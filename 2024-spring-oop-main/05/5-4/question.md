# 奇异的平面形状

## 题目描述

奇异递归模板模式（curiously recurring template pattern，CRTP，可参考[https://en.cppreference.com/w/cpp/language/crtp](https://en.cppreference.com/w/cpp/language/crtp)）是 C++ 模板编程时的一种惯用法：把派生类作为基类的模板参数。例如：

```cpp
template <class T>
class Base {
    // do something...
};
class Derive : public Base<Derive> {
    // do something...
};
```

通过CRTP，可以在 C++ 中实现静态多态。其优点是避免调用虚函数带来的运行时开销，并将重复的代码抽象到基类中，减少派生类中的代码冗余。

在头文件 `Shape.h` 中，你需要实现一个模板类 `Shape<RealShape>`，使用 𝑎,𝑏a,b 两个正整数参数来刻画这个平面形状。在 `Shape` 的基础上派生出一个矩形类 `Rectangle` 和一个直角三角形类 `Triangle`。其中 𝑎,𝑏a,b 在这两个派生类中分别表示“长和宽”和“两条直角边”的长度。

在 `Triangle` / `Rectangle` 中，你均需要实现两个函数：

- `typeImpl()`：返回对应的形状类型（字符串 "Triangle" 或 "Rectangle"）。
- `areaImpl()`：返回对应的形状面积（保证面积是整数，且任何中间运算结果均在int类型的表示范围内）。

在 `Shape<RealShape>` 中，你需要实现如下接口：

- 对应的构造函数和析构函数。
- `type()`：返回 `Shape` 对应的实际形状类型，需要调用 `RealShape` 的具体实现。
- `area()`：返回该平面形状的面积，需要调用 `RealShape` 的具体实现。
- `print()`：输出一行 `Area of [type]: [area]`，其中 `[type]` 和 `[area]` 是形状类型和面积。
- `zoom(int k)`：将该形状的每条边的长度变成原来的 𝑘k 倍。
- `getCreate()`：获取目前总共创建了多少个 `RealShape`（注意不是 `Shape` 的总数）。
- `getAlive()`：获取目前还有多少个 `RealShape` 还未被销毁。

其中 `print()` 和 `zoom(int k)` 还需要支持链式编程，例如 `(new Triangle(2, 3))->zoom(4)->print()`。

你可以定义一些辅助函数，但是上述接口的功能和需求不能随意修改。`Shape<RealShape>`中定义的接口都必须在其类内部实现，而不应该在派生类实现，在测试时我们会以`Shape<RealShape>`为基类，创建其他的派生类。

**注意：实现各成员函数时，不要添加 `const` 修饰符，这可能会导致编译错误！！！**

## 测试样例

我们会把你提交的 `Shape.h` 和 OJ 内置的 `main.cpp`、`Makefile` 放在一起编译，下面是一个示例的 `main.cpp`，其中每组输出均为每个 Subtask 的第一个测试数据。

```cpp
#include <iostream>
#include "Shape.h"

int main() {
#ifdef SUBTASK1
    Rectangle *A = new Rectangle(3, 4);
    std::cout << A->type() << " " << A->area() << "\n";
#endif

#ifdef SUBTASK2
    Triangle *A = new Triangle(2, 5);
    A->zoom(2)->print();
#endif

#ifdef SUBTASK3
    Triangle *A = new Triangle(2, 5);
    std::cout << Triangle::getCreate() << "\n";
    {
        Triangle *B = new Triangle(1, 10);
        std::cout << Triangle::getAlive() << "\n";
        delete B;
    }
    std::cout << Triangle::getCreate() << "\n";
    std::cout << Triangle::getAlive() << "\n";
#endif

#ifdef SUBTASK4
    Rectangle *A[4];
    A[0] = new Rectangle(2, 5);
    for (int i = 0; i < 3; i++) {
        A[i]->print()->zoom(2)->zoom(3)->print();
        A[i + 1] = A[i];
        std::cout << Rectangle::getCreate() << " " << Rectangle::getAlive() << "\n";
    }
#endif
}
```

输出如下：

```plain
Rectangle 12
```

```plain
Area of Triangle: 20
```

```plain
1
2
2
1
```

```plain
Area of Rectangle: 10
Area of Rectangle: 360
1 1
Area of Rectangle: 360
Area of Rectangle: 12960
1 1
Area of Rectangle: 12960
Area of Rectangle: 466560
1 1
```

**该main.cpp文件和提供的示例Makefile、Shape.h可以通过以下链接下载：[点击下载](https://oj.cs.tsinghua.edu.cn/staticdata/1991.6qvSgAyHOC01UmVv.pub/Jx6oLVFV7ddVOLFy.download.zip/download.zip)**

## 子任务要求

本题一共有 4 个子任务，通过子任务中的所有测试点才能得到子任务的分数。

- 子任务 1（20分）：只会调用 `type()` 和 `area()`。
- 子任务 2（20分）：在子任务 1 的基础上，增加了 `print()` 和 `zoom(int)`。
- 子任务 3（20分）：只考察 `getCreate()` 和 `getAlive()` 的正确性，不涉及其他任何函数。
- 子任务 4（40分）：综合考察 CRTP 的实现。

## 提交格式

- 你仅需要提交Shape.h，注意main.cpp，Makefile均由题目提供。
- 你应该将你的文件打包成一个zip压缩包并上传。**注意：你的文件应该在压缩包的根目录下，而不是压缩包的一个子文件夹下。**