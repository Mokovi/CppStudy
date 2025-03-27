#include <iostream>
/*
一、多态的基本概念
    1.多态指同一操作作用于不同类的对象时，可以有不同的行为。通俗来说，通过统一的接口调用不同的实现。在 C++ 中，多态分为两类：
        编译时多态（静态多态）：通过函数重载和模板实现，在编译阶段确定具体调用。
        运行时多态（动态多态）：通过虚函数和继承实现，在运行时根据对象类型决定调用。
    2.运行时多态实现原理：
    动态多态是运行时多态，它依赖于虚函数和继承。通过在基类中声明虚函数，并在派生类中重写（override）该虚函数，我们可以通过基类指针或引用来调用派生类的实现，具体调用哪个函数直到运行时才能确定。
        虚函数表（vtable）：当类中存在虚函数时，编译器会为该类生成一个虚函数表，表中存放着各个虚函数的地址。每个对象内部会包含一个指向虚函数表的指针（vptr）。
        动态绑定：当通过基类指针调用虚函数时，程序会根据 vptr 指向的虚函数表，在运行时找到对应派生类的函数，从而实现动态调用。
    3.注意重写与重载的区别
        重写：子类继承父类后，函数返回值类型、函数名、参数列表完全相同；
        重载：同一个类中，函数名相同，参数列表不同的几个函数，与返回值无关。
    4.纯虚函数和抽象类
        在多态中，通常父类中虚函数的实现是毫无意义的，主要都是调用子类重写的内容，因此可以将虚函数改为纯虚函数。当类中有了纯虚函数，这个类也称为 抽象类
            virtual 返回值类型 函数名（参数列表）= 0 ;
        纯虚函数一般不用实现，但如果提供实现的话，必须在类外定义。
    5.虚析构和纯虚析构
        多态使用时，如果父类析构函数不是虚拟的，那么在对象回收时，父类指针在释放时无法调用到子类的析构代码
            虚析构语法：virtual ~类名(){}
            纯虚析构语法：
                virtual ~类名() = 0;  
                类名::~类名(){}
*/
using namespace std;
// 基类：动物（定义抽象接口）
class Animal {
public:
    virtual void makeSound() const = 0;  // 纯虚函数（抽象类）
    virtual ~Animal() {}                // 虚析构函数（确保正确释放派生类资源）
};

// 派生类：狗
class Dog : public Animal {
public:
    void makeSound() const override {   // 重写虚函数
        cout << "Woof! Woof!" << endl;
    }
};

// 派生类：猫
class Cat : public Animal {
public:
    void makeSound() const override {   // 重写虚函数
        cout << "Meow~" << endl;
    }
};

// 统一接口调用不同对象的实现
void playSound(const Animal& animal) {
    animal.makeSound();
}

int main() {
    Dog dog;
    Cat cat;

    playSound(dog);  // 输出: Woof! Woof!
    playSound(cat);  // 输出: Meow~

    // 通过基类指针数组管理不同对象
    Animal* animals[] = {new Dog(), new Cat()};
    for (Animal* animal : animals) {
        animal->makeSound();
        delete animal;  // 正确调用派生类析构函数（基类析构函数为虚函数）
    }

    return 0;
}