# 选择题

所有题目编译时添加 `--std=c++11`

1. 你正在编写一个脚本，需要复制一个名为`project`的目录及其所有内容到一个新的位置`/backup`。以下哪个命令是正确的？
    
    A. `cp project /backup`
    
    B. `cp -r project /backup`
    
    C. `mv project /backup`
    
    D. `rm -r project/* /backup`
    
2. 【多选】你正在为一个项目编译多个C++源文件 `main.cpp`, `helper.cpp`, 和 `utility.cpp`。你需要生成一个名为 `project` 的可执行文件。下列哪些命令序列可以正确完成编译过程？
    
    A. `g++ -o project main.cpp helper.cpp utility.cpp`
    
    B. `g++ main.cpp helper.cpp utility.cpp -o project`
    
    C. `g++ -c main.cpp helper.cpp utility.cpp && g++ -o project main.o helper.o utility.o`
    
    D. `g++ main.cpp -o project && g++ helper.cpp -o project && g++ utility.cpp -o project`
    
3. 假设有以下两个文件，分别保存在 `main.cpp` 和 `math_utils.cpp` 中：
    
    ```c++
    // File: main.cpp  
    #include <iostream>  
    #include "math_utils.h"  
    
    int main() {  
        std::cout << "Sum: " << add(3, 4) << std::endl;  
        return 0;  
    }  
    // File: math_utils.cpp  
    int add(int a, int b) {  
        return a + b;  
    }  
    ```
    
    并且有一个头文件 `math_utils.h`：
    
    ```c++
    // File: math_utils.h  
    int add(int a, int b);  
    ```
    
    使用 `g++ main.cpp math_utils.cpp -o app` 编译，并运行生成的 `app`，以下说法正确的是： A. 编译错误
    
    B. 运行错误
    
    C. 运行输出"Sum: 7"
    
    D. 无任何输出
    
4. 这段代码运行后，输出结果是什么？
    
    ```c++
    #include <iostream>  
    using namespace std;  
      
    class Counter {  
    private:  
        int count;  
      
    public:  
        void reset() {  
            count = 0;  
        }  
      
        void increment() {  
            count++;  
        }  
      
        int getCount() {  
            return count;  
        }  
    };  
      
    int main() {  
        Counter c;  
        c.reset();  
        c.increment();  
        c.increment();  
      
        cout << c.getCount() << endl;  
      
        return 0;  
    } 
    ```
    
    A. 0
    
    B. 1
    
    C. 2
    
    D. 3
    
5. 在一个日志系统中，我们需要一个函数`logPrint`来输出不同类型的数据。利用函数重载，得到的输出结果是什么？
    
    ```c++
    #include <iostream>  
    #include <string>  
    using namespace std;  
      
    // 函数重载声明  
    void logPrint(int i);  
    void logPrint(double d);  
    void logPrint(string s);  
      
    int main() {  
        logPrint(10);               // 应该调用哪个函数？  
        logPrint(3.14);             // 应该调用哪个函数？  
        logPrint("Hello World");    // 应该调用哪个函数？  
      
        return 0;  
    }  
      
    // 函数重载定义  
    void logPrint(int i) {  
        cout << "Integer: " << i << endl;  
    }  
      
    void logPrint(double d) {  
        cout << "Double: " << d << endl;  
    }  
      
    void logPrint(string s) {  
        cout << "String: " << s << endl;  
    }  
    ```
    
    A. Integer: 10, Double: 3.14, String: Hello World
    
    B. Integer: 10, Integer: 3.14, Integer: Hello World
    
    C. String: 10, String: 3.14, String: Hello World
    
    D. Double: 10, Double: 3.14, String: Hello World
    
6. 在for循环中，变量emp是什么类型？
    
    ```c++
    #include <iostream>  
    #include <vector>  
    using namespace std;  
      
    struct Employee {  
        int id;  
        string name;  
    };  
      
    int main() {  
        vector<Employee> employees = {{1, "Alice"}, {2, "Bob"}};  
      
        for (auto& emp : employees) {  
            cout << "Employee ID: " << emp.id << ", Name: " << emp.name << endl;  
        }  
      
        return 0;  
    }   
    ```
    
    A. int
    
    B. string
    
    C. Employee&
    
    D. 无法确定
    
7. 【多选】下面说法正确的是：
    
    ```c++
    #include <iostream>  
    using namespace std;  
      
    void process(int a, double b) {  
        cout << "Int-double version: " << a << ", " << b << endl;  
    }  
      
    void process(double a, int b) {  
        cout << "Double-int version: " << a << ", " << b << endl;  
    }  
      
    int main() {  
        process(100, 1.5); // Line H  
        process(1.5, 100); // Line I  
      
        return 0;  
    } 
    ```
    
    A. 函数重载不能基于参数顺序的不同
    
    B. 在 Line H 和 Line I 处都没有编译错误
    
    C. 在 Line H 和 Line I 处都存在歧义
    
    D. 函数重载可以基于参数顺序的不同
    
8. 下面哪一个选项是正确的？
    
    ```c++
    #include <iostream>  
    using namespace std;  
      
    #define SQUARE(x) ((x) * (x))  
      
    inline int square(int x) {  
        return x * x;  
    }  
      
    int main() {  
        int a = 5;  
        int result1 = SQUARE(a + 1); // Line X  
        int result2 = square(a + 1); // Line Y  
      
        return 0;  
    }  
    ```
    
    A. Line X 和 Line Y 都会产生相同的汇编代码
    
    B. Line X 和 Line Y 的执行结果不同
    
    C. square函数不会被编译器内联化，因为它的复杂性超出了编译器的优化能力
    
    D. 宏定义SQUARE可能会产生非预期的副作用，而内联函数square不会
    
