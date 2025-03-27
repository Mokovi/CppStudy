#include <iostream>
using namespace std;
/*
一、函数模板
    建立一个通用函数，函数的返回值类型和形参类型可以不具体制定，用一个虚拟的类型来表示
        template <typename/class T>
        函数声明定义
*/
template <class T>
void print(T a, T b)
{
    cout << "调用函数模板" << endl;
}
// 函数可以重载
void print(int a, int b)
{
    cout << "调用普通函数" << endl;
}
// 函数模板也可以重载
template <class T>
void print(T a, T b, T c)
{
    cout << "调用函数模板重载" << endl;
}
void test1()
{
    int a = 1;
    int b = 2;
    int c = 3;
    print(a, b);     // 普通函数
    print(3.4, 3.5); // 函数模板
    // 空模板参数，会强制调用函数模板
    print<>(a, b);  // 函数模板
    print(a, b, c); // 函数模板重载
}
/*
小结：
    1.如果函数模板和普通函数都可以实现，优先调用普通函数
    2.通过空模板参数列表来强制调用函数模板
    3.函数模板也可以重载
*/

/*
二、类模版
    1.建立一个通用类，类中的成员的数据类型是不指定的（不具体）
        template <typename/class T>
        类声明
    2.类模板和函数模板的区别：
        a.自动类型推导方式：
            类模板：没有
            函数模板：有
            类模板使用只能是显示指定类型的方式
        b.模板参数中默认参数：
            类模板：有
            函数模板：没有
            类模板中的模板参数列表可以有默认的参数
    3.类模板的对象作函数参数
        a.指定传入的类型：直接显示对象的数据类型
        b.参数模板化：将对象中的参数变为模板进行传递函数模板
        c.整个类模板化：将这个对象的类型模板化进行传递函数模板
*/
template <class T1, class T2>
class Person
{
public:
    T1 name;
    T2 age;
    Person() {};
    Person(T1 name, T2 age)
    {
        this->name = name;
        this->age = age;
    }
    void printer()
    {
        cout << "name:" << name << ", age:" << age << endl;
    }
};
// 指定传入的类型：直接显示对象的数据类型
void print1(Person<string, int> &p)
{
    p.printer();
}
// 参数模板化：将对象中的参数变为模板进行传递函数模板
template <class T1, class T2>
void print2(Person<T1, T2> &p)
{
    p.printer();
}
// 整个类模板化：将这个对象的类型模板化进行传递函数模板
template <class T>
void print3(T &p)
{
    p.printer();
}
void test2()
{
    Person<string, int> p("张三丰", 99);
    print1(p);
    print2(p);
    print3(p);
}
/*
类模板和继承
    当子类继承父类是一个模板时，子类在声明时，需要指定父类中T的类型.如果不指定，编译器就无法给子类分配内存.
    如果想灵活指定父类中T的类型，子类可以变为类模板
*/
template <class T>
class Base
{
public:
    T a;
};
// 子类继承父类模板
class Son1 : public Base<int> // 父类是类模板，所以要指定类型
{
};

// 子类模板中T1替代（指定）父类模板中的T
template <class T1, class T2>
class Son2 : public Base<T1>
{
public:
    T2 b;
};
/*
类模板成员函数的类外实现:
    类模板中成员函数类外实现时，函数实现之前要加上模板参数列表
*/
template <class T1, class T2>
class Person3
{
    T1 name;
    T2 age;

public:
    // 类内声明
    Person3(T1 name, T2 age);
    void print();
};
// 成员函数类外实现
template <class T1, class T2>
void Person3<T1, T2>::print()
{
    cout << "姓名：" << name << "，年龄：" << age << endl;
}
// 构造函数类外实现
template <class T1, class T2>
Person3<T1, T2>::Person3(T1 name, T2 age)
{
    this->name = name;
    this->age = age;
}
/*
三、模板的扩展特性
    1.非类型模板参数
        模板不仅可以接受类型参数，还可以接受常量参数
    2.模板特化允许针对特定类型提供定制实现。包括全特化和偏特化
    3.模板递归与终止
*/
// 1.非类型模板参数
template <typename T, int N>
class FixedArray
{
private:
    T data[N];

public:
    T &operator[](int index) { return data[index]; }
    int size() const { return N; }
};

void testFixedArray()
{
    FixedArray<int, 5> arr;
    for (int i = 0; i < arr.size(); ++i)
    {
        arr[i] = i * 10;
    }
    for (int i = 0; i < arr.size(); ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}
// 2.特化
template <class T1, class T2>
class TemplateClass
{
public:
    T1 a;
    T2 b;

    TemplateClass(T1 a, T2 b)
    {
        this->a = a;
        this->b = b;
    }
    void func() {}
};
//完全特化
template <>
class TemplateClass<int, string>
{
public:
    int a;
    string b;

    TemplateClass(int a, string b)
    {
        this->a = a;
        this->b = b;
    }
    void func() {} // 特化实现
};
//偏特化
template<class T>
class TemplateClass<T,string>{
    public:
        T a;
        string b;
        TemplateClass(T a, string b){
            this->a = a;
            this->b = b;
        }
        void func(){} //特化的实现
};
//3.递归
// 通用模板（递归定义）
template <int N>
struct Factorial {
    static const int value = N * Factorial<N - 1>::value;
};

// 模板特化终止递归
template <>
struct Factorial<0> {
    static const int value = 1;
};


int main()
{
    cout << "Factorial of 5: " << Factorial<5>::value << endl;
    return 0;
}
