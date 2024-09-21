# 正n边形 圆形 圆柱 圆锥的周长面积体积计算

## 题目描述

根据`main.cpp`、`shape.h`完成:

`circle.h` `circle.cpp` `polygon.h` `polygon.cpp` `cone.h` `cone.cpp` `cylinder.h` `cylinder.cpp`

主函数中第一行会输入正n边形的边数和边长，以及圆形的半径。

主函数中第二行会输入圆柱和圆锥的半径和高。

`π`已在`shape`类中定义。

多边形周长公式：polygonPerimeter=numSides×sideLengthpolygonPerimeter=numSides×sideLength

多边形面积公式：polygonArea=numSides×sideLength24×tan⁡(𝜋/numSides)polygonArea=4×tan(π/numSides)numSides×sideLength2​

圆形周长公式：circlePerimeter=2×𝜋×radiuscirclePerimeter=2×π×radius

圆形面积公式：circleArea=𝜋×radius2circleArea=π×radius2

圆柱表面积公式：cylinderSurfaceArea=2×𝜋×baseRadius2+2×𝜋×baseRadius×heightcylinderSurfaceArea=2×π×baseRadius2+2×π×baseRadius×height

圆柱体积公式：cylinderVolume=𝜋×baseRadius2×heightcylinderVolume=π×baseRadius2×height

圆锥面积公式：coneSurfaceArea=𝜋×baseRadius2+𝜋×baseRadius×slantHeightconeSurfaceArea=π×baseRadius2+π×baseRadius×slantHeight

圆锥体积公式：coneVolume=13×𝜋×baseRadius2×heightconeVolume=31​×π×baseRadius2×height

请在所有代码中的所有变量声明为double类型，最后函数返回类型同样为double，不需要控制输出小数点后的数字位数，主函数中已控制好输出后四位小数。

## 提交格式

提交时请将`circle.h` `circle.cpp` `polygon.h` `polygon.cpp` `cone.h` `cone.cpp` `cylinder.h` `cylinder.cpp`打包在一个压缩文件中，不需要`main.cpp`、`shape.h`和`Makefile`（这三个文件已在系统中给出）。

文件下载地址：[下载链接](https://oj.cs.tsinghua.edu.cn/staticdata/1985.fdcNUyvJO0k3PtFu.pub/HY8TbvGrRWOCzIk0.main.zip/main.zip)

## 输入格式

第一行三个正浮点数，

第二行两个正浮点数。

## 输出格式(其中p、a、v均为浮点数)

Polygon Perimeter: [p]

Polygon Area: [a]

Circle Perimeter: [p]

Circle Area: [a]

Cone Surface Area: [a]

Cone Volume: [v]

Cylinder Surface Area: [a]

Cylinder Volume: [v]

## 输入样例

3 3 3

3 3

## 输出样例

Polygon Perimeter: 9.0000

Polygon Area: 3.8971

Circle Perimeter: 18.8495

Circle Area: 28.2743

Cone Surface Area: 68.2602

Cone Volume: 28.2743

Cylinder Surface Area: 113.0972

Cylinder Volume: 84.8229