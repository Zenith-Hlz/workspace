from networks import ResnetBlock
import torch
import matplotlib.pyplot as plt
from torchvision import datasets, transforms
from torch import nn, optim
from torch.nn import functional as F
from tqdm import tqdm
import os
from dataloader import SKiSDataset
from torch.utils.data import DataLoader

# os.chdir(os.path.dirname(__file__))

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
if SCRIPT_DIR:
    os.chdir(SCRIPT_DIR)

# 创建保存结果的目录
RESULTS_DIR = os.path.join(SCRIPT_DIR if SCRIPT_DIR else ".", "results")
if not os.path.exists(RESULTS_DIR):
    os.makedirs(RESULTS_DIR)


def save_and_show_figure(name):
    """保存图像到指定目录"""
    save_path = os.path.join(RESULTS_DIR, f"{name}.png")
    plt.savefig(save_path)
    plt.close()
    print(f"保存图像到: {save_path}")


"模型结构"


class Encoder(nn.Module):
    def __init__(self, img_size, latent_dim, n_blocks=4):
        super(Encoder, self).__init__()
        self.conv1 = nn.Conv2d(3, 64, kernel_size=3, stride=2, padding=1)
        self.conv2 = nn.Conv2d(64, 128, kernel_size=3, stride=2, padding=1)
        self.conv3 = nn.Conv2d(128, 256, kernel_size=3, stride=2, padding=1)
        self.conv4 = nn.Conv2d(256, 512, kernel_size=3, stride=2, padding=1)
        self.dropout = nn.Dropout(0.5)

        self.resnet_blocks = nn.Sequential(
            *[
                ResnetBlock(
                    512, "reflect", nn.BatchNorm2d, use_dropout=False, use_bias=True
                )
                for _ in range(n_blocks)
            ]
        )

        self.fc_mu = nn.Linear(512 * (img_size // 16) * (img_size // 16), latent_dim)
        self.fc_logvar = nn.Linear(
            512 * (img_size // 16) * (img_size // 16), latent_dim
        )

    def forward(self, x):
        x = torch.relu(self.conv1(x))
        x = torch.relu(self.conv2(x))
        x = torch.relu(self.conv3(x))
        x = torch.relu(self.conv4(x))
        x = self.dropout(x)

        x = self.resnet_blocks(x)

        x = x.view(x.size(0), -1)
        mu = self.fc_mu(x)
        logvar = self.fc_logvar(x)
        return mu, logvar


class Decoder(nn.Module):
    def __init__(self, img_size, latent_dim, n_blocks=4):
        super(Decoder, self).__init__()
        self.img_size = img_size

        self.fc = nn.Linear(latent_dim, 512 * (img_size // 16) * (img_size // 16))

        self.resnet_blocks = nn.Sequential(
            *[
                ResnetBlock(
                    512, "reflect", nn.BatchNorm2d, use_dropout=False, use_bias=True
                )
                for _ in range(n_blocks)
            ]
        )

        self.deconv1 = nn.ConvTranspose2d(
            512, 256, kernel_size=3, stride=2, padding=1, output_padding=1
        )  # Increased filters
        self.deconv2 = nn.ConvTranspose2d(
            256, 128, kernel_size=3, stride=2, padding=1, output_padding=1
        )  # Increased filters
        self.deconv3 = nn.ConvTranspose2d(
            128, 64, kernel_size=3, stride=2, padding=1, output_padding=1
        )  # Increased filters
        self.deconv4 = nn.ConvTranspose2d(
            64, 3, kernel_size=3, stride=2, padding=1, output_padding=1
        )

    def forward(self, z):
        x = torch.relu(self.fc(z))
        x = x.view(x.size(0), 512, self.img_size // 16, self.img_size // 16)

        x = self.resnet_blocks(x)

        x = torch.relu(self.deconv1(x))
        x = torch.relu(self.deconv2(x))
        x = torch.relu(self.deconv3(x))
        x = torch.sigmoid(self.deconv4(x))
        return x


class VAE(torch.nn.Module):
    # 将编码器解码器组合
    def __init__(self, img_size, latent_size):
        super(VAE, self).__init__()
        self.encoder = Encoder(img_size, latent_size)
        self.decoder = Decoder(img_size, latent_size)

    def forward(self, x):  # x: bs,input_size
        # 压缩，获取mu和sigma
        mu, sigma = self.encoder(x)  # mu,sigma: bs,latent_size
        # 采样，获取采样数据
        eps = torch.randn_like(sigma)  # eps: bs,latent_size
        z = mu + eps * sigma  # z: bs,latent_size
        # 重构，根据采样数据获取重构数据
        re_x = self.decoder(z)  # re_x: bs,output_size
        return re_x, mu, sigma


# 损失函数
# 交叉熵，衡量各个像素原始数据与重构数据的误差
loss_BCE = torch.nn.BCELoss(reduction="sum")
# 均方误差可作为交叉熵替代使用.衡量各个像素原始数据与重构数据的误差
loss_MSE = torch.nn.MSELoss(reduction="sum")
# KL散度，衡量正态分布(mu,sigma)与正态分布(0,1)的差异，来源于公式计算
loss_KLD = lambda mu, sigma: -0.5 * torch.sum(
    1 + torch.log(sigma**2) - mu.pow(2) - sigma**2
)

"超参数及构造模型"
# 模型参数
latent_size = 256  # 压缩后的特征维度
hidden_size = 128  # encoder和decoder中间层的维度
img_size = 224

# 训练参数
epochs = 20  # 训练时期
batch_size = 64  # 每步训练样本数
learning_rate = 1e-4  # 学习率
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")  # 训练设备

# 确定模型，导入已训练模型（如有）
modelname = "vae.pth"
model = VAE(img_size, latent_size).to(device)
optimizer = optim.Adam(model.parameters(), lr=learning_rate)
try:
    model.load_state_dict(torch.load(modelname))
    print("[INFO] Load Model complete")
except:
    pass

"训练模型"
train_dataset = SKiSDataset("../SketchyScene-7k/")
val_dataset = SKiSDataset("../SketchyScene-7k/", "val")

train_loader = DataLoader(train_dataset, batch_size=batch_size, shuffle=True)
test_loader = DataLoader(val_dataset, batch_size=batch_size, shuffle=False)

scheduler = optim.lr_scheduler.StepLR(optimizer, step_size=10, gamma=0.5)

# 训练及测试
loss_history = {"train": [], "eval": []}
for epoch in range(epochs):
    # 训练
    model.train()
    # 每个epoch重置损失，设置进度条
    train_loss = 0
    train_nsample = 0
    t = tqdm(train_loader, desc=f"[train]epoch:{epoch}")
    for imgs, lbls in t:  # imgs:(bs,28,28)
        bs = imgs.shape[0]
        # 获取数据
        imgs = imgs.to(device)  # imgs:(bs,28*28)
        # 模型运算
        re_imgs, mu, sigma = model(imgs)
        # 计算损失
        loss_re = loss_BCE(re_imgs, imgs)  # 重构与原始数据的差距(也可使用loss_MSE)
        loss_norm = loss_KLD(mu, sigma)  # 正态分布(mu,sigma)与正态分布(0,1)的差距
        loss = loss_re + loss_norm
        # 反向传播、参数优化，重置
        loss.backward()
        optimizer.step()
        optimizer.zero_grad()
        # 计算平均损失，设置进度条
        train_loss += loss.item()
        train_nsample += bs
        t.set_postfix({"loss": train_loss / train_nsample})
    # 每个epoch记录总损失
    loss_history["train"].append(train_loss / train_nsample)
    # 更新学习率
    scheduler.step()

    # 测试
    model.eval()
    # 每个epoch重置损失，设置进度条
    test_loss = 0
    test_nsample = 0
    e = tqdm(test_loader, desc=f"[eval]epoch:{epoch}")
    for imgs, label in e:
        bs = imgs.shape[0]
        # 获取数据
        imgs = imgs.to(device)
        # 模型运算
        re_imgs, mu, sigma = model(imgs)
        # 计算损失
        loss_re = loss_BCE(re_imgs, imgs)
        loss_norm = loss_KLD(mu, sigma)
        loss = loss_re + loss_norm
        # 计算平均损失，设置进度条
        test_loss += loss.item()
        test_nsample += bs
        e.set_postfix({"loss": test_loss / test_nsample})
    # 每个epoch记录总损失
    loss_history["eval"].append(test_loss / test_nsample)

    # 展示效果
    # 按标准正态分布取样来自造数据
    sample = torch.randn(1, latent_size).to(device)
    # 用decoder生成新数据
    gen = model.decoder(sample)[0].view(3, img_size, img_size)

    plt.close("all")  # 关闭之前的图像

    # 将测试步骤中的真实数据、重构数据和上述生成的新数据绘图
    concat = torch.cat(
        (
            imgs[0].view(3, img_size, img_size),
            re_imgs[0].view(3, img_size, img_size),
            gen,
        ),
        2,
    )
    plt.matshow(concat.permute(1, 2, 0).cpu().detach().numpy())
    save_and_show_figure(f"reconstruction_{epoch}")

    # 显示每个epoch的loss变化
    plt.plot(range(epoch + 1), loss_history["train"])
    plt.plot(range(epoch + 1), loss_history["eval"])
    plt.title(f"Loss at epoch {epoch}")
    plt.xlabel("Epoch")
    plt.ylabel("Loss")
    save_and_show_figure(f"loss_{epoch}")
    # 存储模型
    torch.save(model.state_dict(), modelname)

plt.close("all")

"调用模型"
# 按标准正态分布取样来自造数据
sample = torch.randn(1, latent_size).to(device)
# 用decoder生成新数据
generate = model.decoder(sample)[0].view(3, img_size, img_size)
# 展示生成数据
plt.matshow(generate.permute(1, 2, 0).cpu().detach().numpy())
plt.colorbar()
plt.title("Generated Image")
save_and_show_figure("final_generation")
