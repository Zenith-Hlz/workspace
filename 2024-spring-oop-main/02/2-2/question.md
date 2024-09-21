# 分辨创建与销毁的对象

### 题目描述

有一段不完整的程序，其中6处需要填入代码。请在选项中选代码填入，每个选项只能使用一次，使得程序的输出和标准输出(stdout.txt)一致。（答案可能不唯一，任意一种均可。）

文件下载地址：[下载链接](https://oj.cs.tsinghua.edu.cn/staticdata/1951.EuSoqBrsfyMZd9cR.pub/hSG4aLhTqNsPteYO.download.zip/download.zip)

部分程序预览(main.cpp)：

```c++
#define Option_A A testA = f1(b);
#define Option_B A testB = f2(b);
#define Option_C A testC = f3(b);
#define Option_D A testD = f3(b);
#define Option_E A& testE = f4(b);
#define Option_F A testF = f5(a[0]);

#include "MyAnswer.h"

...

int main()
{
    ...

    //(1)
    cout << "------before call------" << endl;
    Answer1
    cout << "------after return------" << endl << endl;
    
    //(2)
    cout << "------before call------" << endl;
    Answer2
    cout << "------after return------" << endl << endl;

    ...
}
```

你需要编写MyAnswer.h用作选项，以下是一个例子（但不满足要求）

```c++
#define Answer1 Option_A
#define Answer2 Option_B
#define Answer3 Option_C
#define Answer4 Option_D
#define Answer5 Option_E
#define Answer6 Option_F
```

部分标准输出预览(stdout.txt)

A constructing...
A constructing...
B constructing...
A constructing...

......

### 编译选项

`g++ main.cpp -o main`

### 提交方式

提交MyAnswer.h文件，要求能够使和提供的文件共同编译，并能输出与标准输出相同的内容。样例如下：

```c++
#define Answer1 Option_A
#define Answer2 Option_B
#define Answer3 Option_C
#define Answer4 Option_D
#define Answer5 Option_E
#define Answer6 Option_F
```

### 评分标准

OJ评分占100%。