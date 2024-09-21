# 图书馆管理系统

## 题目描述

设计一个简单的图书管理系统，实现以下功能：

1. 添加图书：根据输入的图书信息，将图书添加到系统中。
2. 删除图书：根据输入的图书编号，从系统中删除对应的图书。
3. 查询图书：根据输入的图书编号，查询并显示图书的详细信息。
4. 借阅图书：根据输入的图书编号和借阅者信息，将图书标记为借出状态，并记录借阅者信息。
5. 归还图书：根据输入的图书编号，将借出的图书标记为可借状态，并清除借阅者信息。

## 题目要求

其中 main.cpp、library.h、book.h文件已给出，内容见[下载链接](https://oj.cs.tsinghua.edu.cn/staticdata/1937.OvpweTfaOyE7XDtO.pub/XDQQThULPpNIjZFW.download.zip/download.zip)

1. 完成 `Book` 类，包含以下方法：
    - 获取图书编号（ID）
    - 获取图书名称
    - 获取作者
    - 获取出版社
    - 获取其是否借出的状态
    - 更新其状态（借出->可借；可借->借出）
2. 完成 `Library` 类，用于管理图书，包含以下方法：
    - `add_book`：将图书添加到系统中。
    - `delete_book`：从系统中删除指定编号的图书。
    - `find_book`：根据图书编号查询并显示图书的详细信息。
    - `borrow_Book`：借阅指定编号的图书，并记录借阅者信息。
    - `return_Book`：归还已借出的图书。

## 输入格式

用户通过命令行输入不同的操作指令，包括：

- `ADD`：添加图书，包括图书编号、名称、作者、出版社
- `DELETE`：删除图书
- `FIND`：查询图书
- `BORROW`：借阅图书，需要有借阅者名称
- `RETURN`：归还图书

## 输出格式

根据用户的操作指令，输出相应的结果，包括：

- 添加图书提示
- 删除图书提示
- 查询图书结果
- 借阅图书提示
- 归还图书提示

## 输入示例

第一行包括一个正整数 n，表示操作的个数。

接下来 n 行，每行对应一个操作，并且有操作的相关信息。

```none
12
ADD 123456 Design_Patterns John_Smith Publisher_A
FIND 123456
BORROW 123456 Alice
FIND 123456
RETURN 123456
FIND 123456
FIND 654321
DELETE 123456
DELETE 654321
FIND 123456
BORROW 123456 Alice
RETURN 123456
```

## 输出示例

```none
#1
Added:Design_Patterns
#2
ID:123456
name:Design_Patterns
author:John_Smith
publishing_house:Publisher_A
state:loanable
#3
Borrowed:Design_Patterns
#4
ID:123456
name:Design_Patterns
author:John_Smith
publishing_house:Publisher_A
borrower:Alice
state:borrowed
#5
Returned:Design_Patterns
#6
ID:123456
name:Design_Patterns
author:John_Smith
publishing_house:Publisher_A
state:loanable
#7
Find Failed
#8
Deleted:Design_Patterns
#9
Delete Failed
#10
Find Failed
#11
Borrow Failed
#12
Return Failed
```

## 要求

1. 不修改 main.cpp、library.h、book.h。
2. 在已有代码基础上实现 Library 类和 Book 类。

## 限制与约定

2 ≤ _n_ ≤ 200

字符串的长度不超过 2000

当书籍被`BORROW`后未归还，允许被`DELETE`，这时书籍被正常删除，不应报错。

## 提交格式

根据提供的文件的内容，编写对应的类的代码（Library 类，Book 类）。

你需要提交 `library.cpp book.cpp` 以及Makefile文件。使用的Makefile必须要能生成可执行文件main（不带扩展名）。

**请将你的文件打包成一个 zip 格式的压缩包并上传。注意：你的文件应该在压缩包的根目录下，而不是压缩包的一个子文件夹下，换而言之，解压你提交的压缩包后，应该直接得到一系列 cpp 文件、h 文件等代码文件，而不是一个包含它们的文件夹。**评测时，OJ会将提供的文件贴入你的目录下进行编译并执行。