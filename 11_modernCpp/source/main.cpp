#include <iostream>
#include <vector>
#include <memory>
#include <utility>
#include <cstring>
/*
1. nullptr
    nullptr 出现的目的是为了替代 NULL.
    在 C 中，有些标准库会把 NULL 定义为 ((void*)0) 而有些将它定义为 0. C++ 不允许直接将 void * 隐式转换到其他类型. 因此C++ 只好将 NULL 定义为 0
    C++11 引入了 nullptr 关键字，专门用来区分空指针、0。而 nullptr 的类型为 nullptr_t，能够隐式的转换为任何指针或成员指针的类型，也能和他们进行相等或者不等的比较。

2. constexpr
    constexpr 让用户显式的声明函数或对象构造函数在编译期会成为常量表达式，这个关键字明确的告诉编译器应该去验证修饰内容在编译期就应该是一个常量表达式。类似于 3*4
*/
constexpr int fibonacci(const int n) {
    return n == 1 || n == 2 ? 1 : fibonacci(n-1)+fibonacci(n-2);
}
//从 C++14 开始，constexpr 函数可以在内部使用局部变量、循环和分支等简单语句
constexpr int fibonacci2(const int n) {
    if(n == 1) return 1;
    if(n == 2) return 1;
    return fibonacci2(n-1) + fibonacci2(n-2);
}

/*
3. auto 还不能用于推导数组类型
    在c++20后auto 关键字可以用在参数表里（之前不可以是因为这样的写法会与模板的功能产生冲突,Lambda函数传参可以）
4. decltype
    用法和 typeof 很相似：
        decltype(表达式)
*/

void funcType(){
    auto x = 1;
    auto y = 2;
    decltype(x+y) z;

    if (std::is_same<decltype(x), int>::value)
        std::cout << "type x == int" << std::endl;
    if (std::is_same<decltype(x), float>::value)
        std::cout << "type x == float" << std::endl;
    if (std::is_same<decltype(x), decltype(z)>::value)
        std::cout << "type z == type x" << std::endl;
}

//利用 auto 关键字将返回类型后置、并通过decltype进行推导,需要在编译命令中添加-std=c++20和-fconcepts选项
auto add(auto x, auto y) -> decltype(x+y){
    return x+y;
}
//g++ -std=c++20 -fconcepts main.cpp -o main


//decltype(auto) 主要用于对转发函数或封装的返回类型进行推导，它使我们无需显式的指定 decltype 的参数表达式。
std::string  lookup1(){return "1";}
std::string& lookup2(){
    static std::string str = "hello world!";
    return str;
}
decltype(auto) look_up_a_string_1() {
    return lookup1();
}
decltype(auto) look_up_a_string_2() {
    return lookup2();
}


/*
5.区间 for 迭代
*/
void testFor(){
    std::vector<int> array(5);
    for (auto i : array){
        std::cout << i <<std::endl;
    }
}

/*
6. Lambda表达式
    基本语法:
        [捕获列表](参数列表) mutable(可选) 异常属性 -> 返回类型 {
        // 函数体
        }
    所谓捕获列表，其实可以理解为参数的一种类型，Lambda 表达式内部函数体在默认情况下是不能够使用函数体外部的变量的，
这时候捕获列表可以起到传递外部数据的作用.
    1） 值捕获
        与参数传值类似，值捕获的前提是变量可以拷贝，不同之处则在于，被捕获的变量在 Lambda 表达式被创建时拷贝，而非调用时才拷贝
    2） 引用捕获
        与引用传参类似，引用捕获保存的是引用，值会发生变化。
    3） 隐式捕获，自动捕获函数内部所用到的变量
        [=]（按值捕获）
        [&]（按引用捕获）
        [=, &x]   // 按值捕获所有变量，但x按引用捕获
        [&, x]    // 按引用捕获所有变量，但x按值捕获
        [=, x]    // 非法：隐式和显式均为按值
    4） 表达式捕获
            C++14 给与了我们方便，允许捕获的成员用任意的表达式进行初始化，这就允许了右值的捕获，
    被声明的捕获变量类型会根据表达式进行判断，判断方式与使用 auto 本质上是相同的
    5） 从 C++14 开始，Lambda 函数的形式参数可以使用 auto
*/

void lambda_value_capture() {
    int value = 1;
    auto copy_value = [value] {
        return value;
    };
    value = 100;
    auto stored_value = copy_value();
    std::cout << "stored_value = " << stored_value << std::endl;
    // 这时, stored_value == 1, 而 value == 100.
    // 因为 copy_value 在创建时就保存了一份 value 的拷贝
}

void lambda_reference_capture() {
    int value = 1;
    auto copy_value = [&value] {
        return value;
    };
    value = 100;
    auto stored_value = copy_value();
    std::cout << "stored_value = " << stored_value << std::endl;
    // 这时, stored_value == 100, value == 100.
    // 因为 copy_value 保存的是引用
}

void lambda_implicit_capture(){
    int x = 5, y = 10;

    // 隐式按值捕获x和y
    auto lambda1 = [=] { return x + y; };
    std::cout << lambda1() << std::endl; // 输出15

    // 隐式按引用捕获x和y
    auto lambda2 = [&] { x++; y++; };
    lambda2();
    std::cout << x << " " << y << std::endl; // 输出6 11

    // 混合捕获：按值捕获所有，但按引用捕获x
    auto lambda3 = [=, &x] { x++; return x + y; };
    lambda3();
    std::cout << x << " " << y << std::endl; // 输出7 11
}

void lambda_expression_capture() {
    auto important = std::make_unique<int>(1);
    auto add = [v1 = 1, v2 = std::move(important)](int x, int y) -> int {
        return x+y+v1+(*v2);
    };
    std::cout << add(3,4) << std::endl;
}

/*
7. if constexpr
    将 constexpr 这个关键字引入到 if 语句中, 让代码在编译时就完成分支判断.

8. 类型别名模版
    typedef 可以为类型定义一个新的名称，但是却没有办法为模板定义一个新的名称。因为，模板不是类型。
    C++11 使用 using 引入了下面这种形式的写法，并且同时支持对传统 typedef 相同的功效
        template<typename T>
        using TrueDarkMagic = MagicType<std::vector<T>, std::string>;

9. 1）变长参数模板
            template<typename... Ts> class Magic;
        能够接受不受限制个数的 typename 作为模板的形式参数；如果不希望产生的模板参数个数为 0，可以手动的定义至少一个模板参数。
            template<typename Require, typename... Args> class Magic;
        除了在模板参数中能使用 ... 表示不定长模板参数外，函数参数也使用同样的表示法代表不定长参数，
    这也就为我们简单编写变长参数函数提供了便捷的手段，例如：
        template<typename... Args> void printf(const std::string &str, Args... args);
    2）参数解包
        a. 递归模板函数
        b. 变参模板展开
*/
//递归模版函数进行数据解包
void printf1() {
    std::cout << "End\n";
}
template<typename T, typename... Args>
void printf1(T first, Args... args) {
    std::cout << first << std::endl;
    printf1(args...);      // 递归调用
}
//变参模板展开
template<typename T0, typename... T> void printf2(T0 t0, T... t) {
    std::cout << t0 << std::endl;
    if constexpr (sizeof...(t) > 0) printf2(t...);
}
void testPrintf(){
    printf1("printf1",1,2);
    printf2("printf2",2,5.4);
}

/*
10. 折叠表达式
    C++ 17 中将变长参数这种特性进一步带给了表达式
11. using
    a. 类型别名
        using IntPtr = int*;
    b. 引入命名空间
        using namespace std;//慎用
    c. 继承中的成员引入
            class Base {
            public:
                void func() {}
            };
            class Derived : private Base {
            public:
                using Base::func;     // 将基类的 func 引入到派生类作用域
            };
    d. 别名模板（Alias Template）
        template<typename T> using Ptr = T*;          // 定义指针类型的别名
    e. 构造函数继承
*/
//折叠表达式
template<typename ... T> auto sum(T ... args){
    return (args + ...);
}
void testSum(){
    std::cout << sum(1,2,3,4) <<std::endl;
}

/*
12.面向对象
    a.委托构造
        在构造函数中使用用另一个构造函数。
    b.继承构造
        构造函数如果需要继承是需要将参数一一传递的，这将导致效率低下。C++11 利用关键字 using 引入了继承构造函数的概念
    c.override与final
        override 关键字将显式的告知编译器进行重载，编译器将检查基函数是否存在这样的其函数签名一致的虚函数，否则将无法通过编译。
        final 则是为了防止类被继续继承以及终止虚函数继续重载引入的。
    d.禁用/默认函数
*/
class Base {
public:
    int value1;
    int value2;
    Base() {
        value1 = 1;
        std::cout << "1111\n"; 
    }
    Base(int v2) : Base(){
        value2 = v2;
        std::cout << "2222\n"; 
    }
};
class Derived : public Base{
public:
    int value3;
    using Base::Base;//基类的两个构造函数均继承过来了
    Derived(int v2, int v3):value3(v3), Base::Base(v2){
        std::cout << "3333\n"; 
    }
};
void testGz(){
    Derived d1;
    std::cout << "*******\n";
    Derived d2(12);
    std::cout << "*******\n";
    Derived d3(12,13);
    std::cout << "*******\n";
}

class Singalton{
public:
    Singalton(const Singalton&) = delete;
    Singalton& operator=(const Singalton&) = delete;
    Singalton& getInstance(){
        static Singalton instance;
        return instance;
    }
private:
    Singalton() = default;
    ~Singalton() = default;
};

/*
13. 函数对象包装器
    1) std::function
        std::function 是一种通用、多态的函数封装，它的实例可以对任何可以调用的目标实体进行存储、复制和调用操作，
        它也是对 C++ 中现有的可调用实体的一种类型安全的包裹（相对来说，函数指针的调用不是类型安全的），换句话说，就是函数的容器。
    2) std::bind 与 std::placeholder
        我们可以将部分调用参数提前绑定到函数身上成为一个新的对象，然后在参数齐全后，完成调用
*/
#include <functional>

int foo(int para) {
    return para;
}
void testFunction() {
    // std::function 包装了一个返回值为 int, 参数为 int 的函数
    std::function<int(int)> func = foo;

    int important = 10;
    std::function<int(int)> func2 = [&](int value) -> int {
        return 1+value+important;
    };
    std::cout << func(10) << std::endl;
    std::cout << func2(10) << std::endl;
}

int foo5(int a, int b, int c) {
    return a+b+c;
}
void testbind() {
    // 将参数1,2绑定到函数 foo 上，
    // 但使用 std::placeholders::_1 来对第一个参数进行占位
    auto bindFoo = std::bind(foo5, std::placeholders::_1, 1,2);
    // 这时调用 bindFoo 时，只需要提供第一个参数即可
    std::cout <<"testbind: " <<  bindFoo(1) << std::endl;
}


/*
14. 右值引用 （revalue reference)
    1) 基础概念
        a. 概念
            左值（Left Value）：有名称、可获取地址的持久对象。
                int a = 10;      // a 是左值
                int* p = &a;     // 可以取地址
            右值（Right Value）：临时对象、字面量或即将销毁的对象，不可取地址。
                42;             // 字面量是右值
                a + 1;          // 表达式结果是右值
                std::move(a);   // 强制转换为右值
        b. 目的：解决不必要的拷贝，提升性能（尤其是对临时对象的处理）
        c. 语法：用 && 声明右值引用，只能绑定到右值
                int&& rref = 42;          // 正确：绑定到字面量
                int&& rref2 = a;          // 错误：a 是左值
                int&& rref3 = std::move(a); // 正确：强制转换后绑定
    2） 移动语义（Move Semantics）
        a.深拷贝
        b. 移动构造函数（Move Constructor）
        c. 移动赋值运算符（Move Assignment）
    3) std::move
        用途：将左值标记为“可移动的右值”，触发移动语义。
        注意std::move 不实际移动资源，只是类型转换。
    4）完美转发（Perfect Forwarding）
        T&& 在模板推导中可能是左值或右值引用
        std::forward 的作用：根据模板参数 T 的类型，选择保留左值或右值特性
            template<typename T>
            void relay(T&& arg) {
                target(std::forward<T>(arg)); // 完美转发
            }
*/
class String {
public:
    char* data;
    // 构造函数
    String(const char* str) {
        data = new char[strlen(str) + 1];
        strcpy(data, str);
    }
    // 拷贝构造函数（深拷贝）
    String(const String& other) {
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
    }
    // 移动构造函数
    String(String&& other) noexcept {
        data = other.data;    // 直接接管资源,没用赋值步骤，极大节约了资源
        other.data = nullptr; // 原对象置空，防止重复释放
    }
    // 移动赋值运算符
    String& operator=(String&& other) noexcept {
        if (this != &other) {
            delete[] data;       // 释放当前资源
            data = other.data;   // 接管资源
            other.data = nullptr;
        }
        return *this;
    }
    ~String() { delete[] data; }
};
/*
注意事项：
    1. 移动操作应标记为 noexcept，否则某些容器（如 std::vector）可能回退到拷贝。
    2. 若未声明拷贝控制函数（拷贝构造、析构等），编译器会生成默认移动操作。若声明了拷贝构造函数或析构函数，编译器不会生成默认移动操作。
*/


int main(){
    int arr[fibonacci(3)];
    std::cout<< sizeof(arr)/sizeof(int) << std::endl;

    funcType();
    std::cout << add(3,4) << std::endl;

    testPrintf();
    testSum();
    testGz();
    testFunction();


    return 0;
}