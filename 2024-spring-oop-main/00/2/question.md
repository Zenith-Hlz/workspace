# 图书管理系统

## 题目说明

[English Version](https://oj.cs.tsinghua.edu.cn/staticdata/2023.EpWpmGduzpVD5elU.pub/ssme11VZbcUcPq7U.LibraryManagementSystem.pdf/LibraryManagementSystem.pdf)

在一个神奇的图书馆中，有各种各样的Book，每一本书都有其独特的信息。请设计一个图书类 `Book` 和一个图书馆类 `Library`，要求：

`Book` 和 `Library` 都需要使用类模板的方式，使得既能够创建属性为整数的对象，也能创建属性为实数的对象。

`Book` 类通过传入Book name（字符串）、Author（字符串）和Pages（整数或实数）进行初始化；`Library` 类可以添加Book并进行管理。

`Book` 具有如下两个接口：

`void show()`：输出Book的Book name、Author和Pages，格式为：`Book name: title, Author: author, Pages: pages`，最后添加一个换行符。

`bool operator<(const Book<T>& other)`：重载 `<` 运算符，比较两本书的Pages大小。

`Library` 具有如下三个接口：

`void addBook(const Book<T>& book)`：将一本书添加到图书馆。

`void show()`：输出图书馆中所有Book的信息，每本书的信息占一行。输出的顺序必须与添加的顺序一致。

`void borrowBook(const std::string& title)`：传入Book name，判断图书馆中是否有这本书，并输出相应结果。如果有，输出 `Books Checked out title.`；否则输出 `Book title does not exist.`。注意，该函数只检查书是否存在，不需要把书从图书馆中移除。总体书的数量不大，顺序查找也可以AC。

在本题中，我们假设Pages的数据类型相同。

一种使用 `Book` 类和 `Library` 类的示例为：

```cpp
#include<iostream>
#include"Book.h"
#include"Library.h"
using namespace std;

int main() {

    Library<int> library;
    Book<int> book1("The Catcher in the Rye", "J.D. Salinger", 277);
    Book<int> book2("To Kill a Mockingbird", "Harper Lee", 324);

    library.addBook(book1);
    library.addBook(book2);
    library.show();
    // 此处应该输出:
    // Book name: The Catcher in the Rye, Author: J.D. Salinger, Pages: 277
    // Book name: To Kill a Mockingbird, Author: Harper Lee, Pages: 324

    library.borrowBook("The Catcher in the Rye");
    // 此处应该输出: Books Checked out The Catcher in the Rye.
    
    library.borrowBook("1984");
    // 此处应该输出: Book 1984 does not exist.

    Book<int> book3("1984", "George Orwell", 328);
    if (book2 < book3) book2.show();
    else book3.show();
    // 此处应输出: Book name: To Kill a Mockingbird, Author: Harper Lee, Pages: 324

    return 0;
}
```

### 提交格式

- 你需要提交多个文件，包含 `Book.h`, `Library.h` 文件；不需要上传 `main.cpp` 和 `Makefile` 文件。
    
- 你应该将你的文件打包成一个 zip 压缩包并上传。**注意：你的文件应该在压缩包的根目录下，而不是压缩包的一个子文件夹下。** 评测时，OJ 会将提供的 `main.cpp` 贴入你的目录下进行编译并执行。