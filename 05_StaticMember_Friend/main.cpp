#include <iostream>
/*
一、静态成员
    在成员变量和成员函数前加上关键字static，称为静态成员
    1.静态成员变量
        a.一般类内声明，类外初始化
        b.所有对象共享同一份数据,脱离了对象的概念，只与类有关
        c.在编译阶段分配内存
        d.静态成员变量访问方式:通过对象访问;通过类名访问.
        e.静态成员变量也是具有访问权限的,私有权限类外访问不到
    2.静态成员函数
        a.所有对象共享同一个函数,脱离了对象的概念，只与类有关
        b.静态成员函数只能访问静态成员变量
        c.静态成员函数也是具有访问权限的,私有权限类外访问不到
    3.应用场景
        a.静态成员变量的应用场景：
            统计对象的数量
            共享数据
            常量数据
        b.静态成员函数的应用场景
            访问静态成员变量
            实现工具函数
            单例模式
*/
class Person{
public:
    Person(int age):age(age){
        count++;
    }
    void show(){
        std::cout << "count = " << count << std::endl;
    }
    static void numPlus();
    static int num;
private:
    static int count;
    int age;
};
int Person::count = 0;
int Person::num = 0;
void Person::numPlus(){
    num++;
    //std::cout<<"age = " << age << std::endl; 报错静态成员函数，只能访问静态成员变量
}
void testStaticMem()
{
    Person::numPlus();
    std::cout << Person::num <<std::endl;
    Person a(11),b(20),c(32);
    a.show();
}
/*
二、友元
    目的：让一个函数或者类 访问另一个类中私有成员
    1.友元的三种实现
        都是在类内加一条声明语句.
        a.全局函数做友元
        b.类做友元
        c.成员函数做友元
    2.友元机制一定程度上破坏了类的封装性，但可以在必要时提高灵活性，如 调试、特殊访问权限、运算符重载等。
    3.注意：
        被声明为友元的类本身并不能直接访问友元类的成员，仍然需要通过成员函数访问。
        友元关系是单向的
*/
//a.全局函数做友元
class PrivateData {
    friend void showData(const PrivateData& obj);
private:
    int data;
public:
    PrivateData(int d) : data(d) {}
};
void showData(const PrivateData& obj) {
    std::cout << "Private data: " << obj.data << std::endl;
}
void testGlobalFunc() {
    PrivateData obj(42);
    showData(obj); // 访问私有成员
}
//b.类做友元
class Secret {
    friend class FriendClass;
private:
    int secretCode;
public:
    Secret(int code) : secretCode(code) {}
};
class FriendClass {
public:
    void revealSecret(const Secret& s) {
        std::cout << "Secret Code: " << s.secretCode << std::endl;
    }
};
void testClassFriend() {
    Secret s(1234);
    FriendClass f;
    f.revealSecret(s); // 访问 Secret 的私有成员
}
//c.成员函数做友元 注意需要前置声明
// 先前置声明 SecretData
class SecretData;
class AnotherClass {
public:
    void accessSecret(const SecretData& obj);
};
class SecretData {
private:
    int data;
public:
    SecretData(int d) : data(d) {}
    friend void AnotherClass::accessSecret(const SecretData& obj);
};
void AnotherClass::accessSecret(const SecretData& obj) {
    std::cout << "Accessing secret data: " << obj.data << std::endl;
}
void testClassMem() {
    SecretData s(99);
    AnotherClass a;
    a.accessSecret(s); // 访问私有数据
}
int main()
{
    testStaticMem();
    testGlobalFunc();
    testClassFriend();
    testClassMem();
    return 0;
}