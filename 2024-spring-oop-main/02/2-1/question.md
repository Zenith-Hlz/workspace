# 选择题

所有题目编译时添加 `--std=c++11`

1. 【单选题】关于类的构造函数和析构函数，以下哪个描述是错误的？
    
    A. 析构函数用于清理对象占用的资源。
    
    B. 一个类可以有多个析构函数。
    
    C. 构造函数可以被重载。
    
    D. 析构函数在对象销毁时自动调用。
    
2. 【单选题】考虑下面的C++代码段，请问输出什么？
    
    ```c++
    #include <iostream>
    using namespace std;
    
    class Box {
    public:
        static int objectCount;
        Box() { ++objectCount; }
        ~Box() { --objectCount; }
    };
    
    int Box::objectCount = 0;
    
    int main() {
        Box box1;
        Box* box2 = new Box;
        cout << Box::objectCount << endl;
        delete box2;
        cout << Box::objectCount << endl;
        return 0;
    }
    ```
    
    A. 2 2
    
    B. 2 1
    
    C. 1 1
    
    D. 1 0
    
3. 【多选题】在C++中使用new和delete操作符时，下列哪项描述是正确的？
    
    A. 使用new时必须使用delete释放内存。
    
    B. 使用new[]创建的数组，可以用delete而不是delete[]释放。
    
    C. 使用delete释放未通过new分配的内存是安全的。
    
    D. new和delete帮助管理动态分配的内存。
    
4. 【单选题】关于析构函数和友元，阅读下列代码，并选出正确的选项：
    
    ```c++
    #include <iostream>
    
    class Student{
        friend class School;
    private: // (B)
        ~Student(){std::cout<<"Student fired.";}
    public:
        class School* school;
        void interfereSchool();
    };
    
    class School{
    private:
        void access(){std::cout<<"School accessed.";}
    public:
        Student* student;
        void fireStudent();
    };
    
    void Student::interfereSchool(){
        school -> access(); // (A)
    }
    void School::fireStudent(){
        delete student;
    }
    
    int main(){
    School* school = new School();
    Student* student = new Student();
    school -> student = student;
    student -> school = school;
    
    student -> interfereSchool();
    school -> fireStudent();
    }
    ```
    
    A. 该代码**不能**通过编译。原因：`Student` 类的 `interfereSchool` 成员函数访问了 `School` 类的私有成员 `access`。解决方案：删除该调用（即：删除代码中注释 `(A)` 所在的行），方可通过编译。
    
    B. 该代码**不能**通过编译，原因：`Student` 类的析构函数被定义为私有成员。解决方案：将其更改为公有成员（即：将代码中注释 `(B)` 所在的行改为 `public:`），方可通过编译。
    
    C. 该代码**不能**通过编译，且 A、B 所述原因都正确，因此必须同时应用 A、B 的解决方案，该代码才能通过编译。
    
    D. 该代码**可以**通过编译，且输出结果为 `School accessed.Student fired.` 。
    
5. 【单选题】考虑以下C++类定义，哪个描述是正确的？
    
    ```c++
    class MyClass {
        int a;
    public:
        MyClass(int x) : a(x) {}
        friend void showA(MyClass& x);
        void increment() { ++a; }
    };
    
    void showA(MyClass& x) {
        cout << "MyClass a=" << x.a << endl;
    }
    
    void incrementAndShowA(MyClass& x) {
        x.increment();
        showA(x);
    }
    ```
    
    A. `showA`是`MyClass`的成员函数。
    
    B. 友元函数`showA`可以访问`MyClass`的私有成员`a`。
    
    C. `incrementAndShowA`函数可以直接修改`MyClass`对象的私有成员`a`的值，不通过任何公有或友元函数。
    
    D. `incrementAndShowA`尝试直接访问`MyClass`的私有成员`a`，这将导致编译错误。
    
6. 【单选题】考虑以下C++代码片段，关于运算符重载的描述中，哪一个是正确的？
    
    ```c++
    class Complex {  
    public:  
        double real;  
        double imag;  
    
        Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}  
    
        // 运算符重载函数  
        Complex operator+(const Complex& rhs) const {  
            return Complex(real + rhs.real, imag + rhs.imag);  
        }  
    
        // 其他成员函数...  
    };  
    
    int main() {  
        Complex c1(1.0, 2.0);  
        Complex c2(3.0, 4.0);  
        Complex sum = c1 + c2; // 使用重载的+运算符  
        return 0;  
    }
    ```
    
    A. 运算符重载函数`operator+`必须返回指向新创建的`Complex`对象的指针。
    
    B. 运算符重载函数`operator+`可以作为类的非成员函数实现。
    
    C. 在`main`函数中，`c1 + c2`表达式会调用`Complex`类的默认构造函数。
    
    D. 重载的`operator+`函数改变了`+`运算符原有的语义。
    
7. 【多选题】静态成员函数的特点是什么？
    
    A. 可以访问类的非静态成员变量。
    
    B. 可以通过类名直接调用。
    
    C. 不能声明为const。
    
    D. 只能访问类的静态成员变量。
    
8. 【单选题】考虑以下C++类定义，选择正确的选项。
    
    ```C++
    class Test {
    public:
        static const int num = 10;
        int array[num];
        Test() {}
    };
    ```
    
    A. 类定义因为静态成员`num`而编译失败。
    
    B. 静态常量成员`num`可以在类内初始化。
    
    C. `array`的大小必须在构造函数中确定。
    
    D. `num`必须在类外进行初始化。