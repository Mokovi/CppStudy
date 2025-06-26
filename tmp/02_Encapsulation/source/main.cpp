#include <iostream>
#include "calculator.h"

/*
    面向过程：
            关注的是如何解决问题、以及解决问题的步骤
    面向对象：
        抽象：先找出(想象出)能解决问题的"对象"，分析该对象解决问题所需要的属性(成员变量)和行为(成员函数)
        封装：把抽象的结果封装成一个类(结构)，并给的类的成员变量、成员函数设置相应的访问权限
        (public\protected\private)
        继承：
            1、在封装类之前先考虑现有的类是否有能解决一部分问题，如果有则把现有的类继承过来，在此基础上进行扩展，以此来节约解决问题的时间
            2、把一个复杂的问题分析拆解成若干个小问题，每个问题设计一个类去解决，最后把这些类通过继承合并到一个能解决最终问题的类中
        多态：
            发出一个指令、系统会根据实际情况执行不同相应的操作，这种特征称之为多态(统一命令多种形态)
            例如重载过的函数，当调用函数时，编译器会根据参数的类型调用对应的重载版本，这就是一种多态
            而且具体调用哪个版本如果在编译时就能确定下来，这种重载称为编译时多态
        
    特别注意：面向对象的行为细节依然是面向过程，因此面向对象只是从更高的维度去思考解决问题，而不是寻求解决问题的捷径
*/

/*
一、函数重载
    1、什么是函数重载
        在同一个作用域下，函数名相同、参数列表(参数个数或类型)不同的函数构成重载关系
        函数重载与返回值类型、参数名无关
    2、C++是如何实现函数重载的
        通过g++ -S xxx.cpp 生成汇编代码得知，编译器会把函数的参数类型缩写后追加到函数名后面，也就是说编译时会给函数进行换名
    3、extern "C"
        因为C++编译器在编译函数调用语句时，会找换名后的函数调用，这样就无法调用到已经使用C编译器编译成功的函数了
        使用 extern "C" 会让C++编译器按照C编译器的格式来翻译函数名，这样函数的声明与定义就匹配，就可以正确地调用C标准库、系统库函数
    4、重载和隐藏
        在同一作用域下同名不同参的函数构成重载关系
        在不同作用域(父子类)下的同名函数遵循名字隐藏原则
*/
// 函数重载示例
void print(int x) {
    std::cout << "Integer: " << x << std::endl;
}

void print(double x) {
    std::cout << "Double: " << x << std::endl;
}

void print(const std::string& str) {
    std::cout << "String: " << str << std::endl;
}

// extern "C" 示例
extern "C" void cFunction() {
    std::cout << "This is a C function." << std::endl;
}

// 名字隐藏示例
class Base {
public:
    void show() { std::cout << "Base show()" << std::endl; }
};

class Derived : public Base {
public:
    void show(int x) { std::cout << "Derived show(int): " << x << std::endl; }
};

/*
二、默认形参
    1、什么是默认形参
        C++中可以给函数的参数设置默认值，当函数调用者提供了实参则使用实参，如果没有提供则使用默认值
    2、默认形参要靠右
        如果函数有多个参数，设置了默认形参，必须遵循从右往左依次设置，否则有二义性
    3、只能在函数声明处设置默认形参
        如果函数声明与定义分开实现，只能在函数声明时设置默认形参，否则语法错误(需要调用才看到错误)
*/
void greet(const std::string& name, const std::string& greeting = "Hello") {
    std::cout << greeting << ", " << name << "!" << std::endl;
}

/*
三.this 指针的介绍
    this 指针是C++类中的一个特殊指针，它指向调用成员函数的当前对象。this 主要用于以下几种情况：
    1.区分成员变量和形参
        当成员变量和形参同名时，可以使用 this-> 访问成员变量。
    2.返回对象本身
        this 指针可用于在成员函数中返回当前对象，以支持方法链调用。
    3.避免对象拷贝
        在拷贝赋值运算符 operator= 中，this 可用于判断自赋值 if (this == &other)，避免重复赋值。
    4.指向当前对象
        适用于 operator*, operator-> 等重载运算符，返回自身的指针或引用。
*/
class Person {
    private:
        std::string name;
        int age;
        
    public:
        // 构造函数
        Person(const std::string& name, int age) : name(name), age(age) {
            std::cout << "Person Constructor: " << this->name << " created." << std::endl;
        }
        
        // 析构函数
        ~Person() {
            std::cout << "Person Destructor: " << this->name << " destroyed." << std::endl;
        }
        
        // 使用 this 指针区分成员变量
        void setName(const std::string& name) {
            this->name = name;
        }
        
        // 返回 this 指针支持方法链调用
        Person* setAge(int age) {
            this->age = age;
            return this;
        }
        
        void introduce() {
            std::cout << "Name: " << this->name << ", Age: " << this->age << std::endl;
        }
        
        // 拷贝赋值运算符，防止自赋值
        Person& operator=(const Person& other) {
            if (this == &other) return *this; // 避免自赋值
            this->name = other.name;
            this->age = other.age;
            return *this;
        }
    };


int main(void)
{   
    Calculator cal(1.2, 1.3);
    std::cout << cal.add() << std::endl;
    std::cout << cal.minus() << std::endl;
    std::cout << cal.multiply() << std::endl;
    std::cout << cal.divide() << std::endl;
    
     // 调用函数重载
     print(10);
     print(3.14);
     print("Hello, C++");
     
     // 调用 extern "C" 的 C 函数
     cFunction();
     
     // 名字隐藏示例
     Derived d;
     d.show(42);
     // d.show(); // 编译错误，Base::show() 被隐藏
     d.Base::show(); // 正确调用 Base::show()
     
     // 默认形参示例
     greet("Alice");
     greet("Bob", "Hi");

     //测试this用法
    Person p1("Alice", 30);
    p1.introduce();
    
    // 返回 this 指针支持方法链调用
    p1.setAge(35)->introduce();
    
    // 拷贝赋值运算符，防止自赋值
    Person p2("Charlie", 40);
    p2 = p1;
    p2.introduce();


    return 0;
}