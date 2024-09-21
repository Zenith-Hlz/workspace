# 树洞管理

### 题目描述

- 树洞是一个校内同学互相匿名交流的公共平台，作为树洞的管理员，你管理了若干个帖子。现在你要写一个程序，（1）支持封禁帖子的操作，即`ban x y z`，代表第`x`个帖子的第`y`个回复将不会被展现，该操作由`id`为`z`的管理员提交；（2）查询封禁情况的操作，即`query x y`，返回第`x`个帖子的第`y`个回复的封禁状况。管理员的`id`可能为`string`类型，也可能是`int`类型，程序需要支持这两种类型。请你根据抽象类`Container`实现所需接口。

### 输入样例

- 第一行是管理员的`id`类型，为`int`或`string`；第二行是一个整数 `n` ，表示操作的总数。 接下来 `n` 行，每行描述一个操作。首先是一个字符串，有两种可能：（1）`ban`代表一个封禁操作；（2）`query`，代表查询操作。字符串之后是帖子的序号和回复的序号。

```bash
string
8
ban 5 3 Wang
ban 3 4 Huang
ban 6 2 Musk
ban 4 1 Shi
query 3 2
query 5 3
query 4 1
query 6 1
```

### 输出样例

```bash
open
Wang
Shi
open
```

- 对每个查询操作，输出一行为查询的答案，若帖子未被封禁，返回`open`；反之，直接返回执行该操作的管理员的`id`。

### 限制与约定

- 0 < `n` ≤≤ 1000
- 帖子的序号和回复的序号均为整数，在`int`类型范围内，均不超过100000。所有帖子的回复的初始状态均为未封禁。管理员`id`可能为`int`或是`string`，字符串的长度不超过 25。

### 要求

- 我们提供了`Makefile`和测试文件`main.cpp`（[点此下载](https://oj.cs.tsinghua.edu.cn/staticdata/1986.xNcQtdYwXP7NgYal.pub/zoyNVKE19JZ1Rlnw.download.zip/download.zip)）。
- 你需要提交头文件`Container.h`。
- 你应该将你的文件打包成一个zip压缩包并上传。注意：你的文件应该在压缩包的根目录下，而不是压缩包的一个子文件夹下。评测时，OJ会将提供的Makefile和main.cpp贴入你的目录下进行编译并执行。