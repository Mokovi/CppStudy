#include<iostream>
#include<cstring>
/*
运算符重载
    运算符重载允许程序员为自定义类型（类或结构体）赋予与内置类型相似的运算符行为。通过重载运算符，可以使代码更直观、简洁，例如用 + 直接操作两个对象，而不是调用函数。
    1.可重载的运算符：
        a.大多数运算符可以重载（如 +, -, *, /, ==, <<, >>, [], (), new, delete等）。
        b.不可重载的运算符：::（作用域解析）、.（成员访问）、.*（成员指针访问）、?:（条件运算符）、sizeof、typeid。
    2.运算符的语义：
        a.不能改变运算符的优先级和结合性。
        b.至少有一个操作数是自定义类型（不能为内置类型重载运算符）。
    实现方式：
        a.成员函数：运算符的第一个操作数是当前类的对象（如 a + b，a 是当前对象）。
        b.友元函数或全局函数：运算符的第一个操作数不是当前类的对象（如 cout << obj，cout 是 ostream 类型）。
    3.注意事项
        a. 全局重载new、delete时，会影响所有使用 new 和 delete 的动态内存分配。
        b. 类的new delete默认为static的，只能访问静态成员变量
*/
//1. 算术运算符重载（+）,输入输出运算符重载（<< 和 >>）,递增运算符重载（++a,a++)
class Complex {
private:
    double real, imag;
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}    
    // 重载 '+' 运算符（成员函数形式）
    Complex operator+(const Complex& other) const { //多用引用作为形参，该函数的形参改为Complex other也能实现，但是会多一个复制的步骤，直接使用引用会更高效，此外const也要多使用
        return Complex(real + other.real, imag + other.imag);
    }
    /*
    // 重载 '+' 运算符(友元函数形式)
    friend Complex operator+(const Complex& a, const Complex& b);
    */
    
    // 重载输出运算符 <<（必须为友元函数）
    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
    
    // 重载输入运算符 >>（必须为友元函数）
    friend std::istream& operator>>(std::istream& is, Complex& c);
    void show(){
        std::cout << "real = " << real << " imag = " << imag << std::endl; 
    }
    // 重载前置递增运算符 (++c)
    Complex& operator++() {
        ++real;
        ++imag;
        return *this;
    }
    // 重载后置递增运算符 (c++)
    Complex operator++(int) {
        Complex temp = *this;
        ++(*this);
        return temp;
    }
};
/*
// 重载 '+' 运算符,友元函数实现
Complex operator+(const Complex& a, const Complex& b) {
    return Complex(a.real + b.real, a.imag + b.imag);
}
*/
std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << "(" << c.real << " + " << c.imag << "i)";
    return os;
}
std::istream& operator>>(std::istream& is, Complex& c) {
    std::cout << "Enter real and imaginary parts: ";
    is >> c.real >> c.imag;
    return is;
}

void testOpPlus(){
    Complex c1(1, 2), c2(3, 4);
    Complex c3 = c1 + c2; // 调用 operator+
    c3.show();

    Complex c;
    std::cin >> c;
    std::cout << c << std::endl;

    // 测试前置递增
    std::cout << "c1 = " << c1 << std::endl;
    std::cout << "++c1 = " << ++c1 << std::endl;
    
    // 测试后置递增
    std::cout << "c1++ = " << c1++ << std::endl;
    std::cout << "c1 after c1++ = " << c1 << std::endl;

}
//2.关系运算符 ==
class Point {
private:
    int x, y;
public:
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    
    // 重载 '==' 运算符
    bool operator==(const Point& other) const {
        return (x == other.x) && (y == other.y);
    }
};
void testOpEqual(){
    Point p1(1, 2), p2(1, 2);
    if (p1 == p2) {
        std::cout << "Points are equal!" << std::endl;
    }
    
}
//3.下标运算符
class Array {
private:
    int arr[10];
public:
    // 重载下标运算符（用于读写元素）
    int& operator[](int index) {
        if (index < 0 || index >= 10) {
            throw std::out_of_range("Index out of range!");
        }
        return arr[index];
    }
};
void testSubscript(){
    Array a;
    a[3] = 42;    // 写入
    std::cout << a[3] << std::endl;  // 读取
}
//4. 函数运算符
class Adder {
private:
    int value;
public:
    Adder(int v) : value(v) {}
    
    // 重载 () 运算符（函数对象）
    int operator()(int x) const {
        return value + x;
    }
};
void testOpFunc(){
    Adder add5(5);//首次调用构造函数
    std::cout << add5(3) << std::endl; // 输出 8（等价于 add5.operator()(3)）
}

//5.赋值运算符以及拷贝构造函数
class String {
private:
    char* data;
public:
    //构造函数
    String(const char* str = "") {
        data = new char[strlen(str) + 1];
        strcpy(data, str);
    }
    //拷贝构造函数
    String(const String& other) {
        data = new char[strlen(other.data) + 1]; // 分配内存
        strcpy(data, other.data);
    }

    // 重载赋值运算符（深拷贝）
    String& operator=(const String& other) {
        if (this != &other) {
            delete[] data;
            data = new char[strlen(other.data) + 1];
            strcpy(data, other.data);
        }
        return *this;
    }
    void show()
    {
        puts(data);
    }
    ~String() { delete[] data; }
};
void testCopy(){
    String s1("Hello"), s2;
    s2 = s1; // 调用 operator=
    s2.show();
    String s3 = s1;
    s3.show();
}




int main()
{
    //testCopy();
    //testOpPlus();
    //testOpEqual();
    testOpFunc();
    testSubscript();
    return 0;
}