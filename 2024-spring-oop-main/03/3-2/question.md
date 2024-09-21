# 圆形

### 题目描述

现有一段计算图形面积的程序如下：

```c++
#include <iostream>
#include "Shape.h"
using namespace std;
int main() {
    double width,height;
    cin>>width>>height;
    Shape* rectangle = new Rectangle(width,height);
    cout<<rectangle->getArea()<<endl;

    double radius;
    cin>>radius;
    Shape* circle = new Circle(radius);
    cout<<circle->getArea()<<endl;

    delete rectangle;
    delete circle;
    return 0;
}
```

要求实现矩形(Rectangle)和圆形(Circle)的面积计算。矩形和圆形继承自图形基类(Shape)。

圆周率 𝜋π 取 3.14。

### 输入样例

对矩形，输入宽和高；对圆形，输入半径。输入均为正数。

```none
4 4
1
```

### 输出样例

```none
16
3.14
```

### 要求

1. 不修改 `main.cpp`。
2. 在已有代码基础上编写 `Shape.h`、`Shape.cpp`。 其中包含 Shape 类，Rectangle 类，Circle 类。Rectangle 类和 Circle 类要继承自 Shape 类。 文件下载：[下载链接](https://oj.cs.tsinghua.edu.cn/staticdata/1966.N8TzediZMYv6Ck1X.pub/1cZI9xd8mTMibG2h.main.cpp/main.cpp)

### 限制与约定

0≤𝑤𝑖𝑑𝑡ℎ,ℎ𝑒𝑖𝑔ℎ𝑡,𝑟𝑎𝑑𝑖𝑢𝑠≤1000≤width,height,radius≤100

**时间限制：1s**

**空间限制：256MB**

### 提交格式

根据提供的 `main.cpp` 的内容，在 `Shape.h`、`Shape.cpp` 中编写所需的类的代码（ Shape 类，Rectangle 类，Circle 类）。评测时，OJ会将提供的 `main.cpp`，`Makefile`贴入你的目录下进行编译并执行。 将`Shape.h`、`Shape.cpp` 一起打包为一个zip文件提交

### 评分标准

OJ评分占100%