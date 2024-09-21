# Makefile与多文件编译

### 题目描述

现在已有main.cpp、product.cpp、sum.cpp、functions.h四个文件。

文件内容见[下载链接](https://oj.cs.tsinghua.edu.cn/staticdata/1933.mwN88l1YbmoYNZZX.pub/gnHz4uDSLdOIQFMa.download.zip/download.zip)

你需要编写一个Makefile文件完成程序的编译过程，要求：

- 在linux系统下，Makefile文件能正常运行。（编译器为g++。）
    
- 使用make命令，能够联合编译多个源文件，最终生成名为main的可执行文件。（linux下无exe后缀。）main可以正常执行，其输出请查看示例。
    
- 使用make debug命令，能够生成开启调试模式的可执行文件，同样生成名为main的可执行文件。调试模式的具体输出请查看示例。
    
- 使用make clean命令，能够清理之前生成的文件，还原成最初的样子。
    

提示：你可能会用到 g++/gcc 的一些[编译选项](https://gcc.gnu.org/onlinedocs/gcc/Preprocessor-Options.html)。

**注意：你Makefile文件在结束任务后必须返回0。若返回非0值，则认为make失败，评测系统会给出Make Error的提示。**

### 输入样例

```none
1 1
```

### 输出样例

```none
2
1
```

### 调试模式输入样例

```none
1 1
```

### 调试模式输出样例

```none
running sum(a = 1, b = 1)
2
running product(a = 1, b = 1)
1
```

### 提交要求

提交一个仅包含Makefile的zip文件，满足上述需求。

### 评分标准

OJ自动评测占100%。