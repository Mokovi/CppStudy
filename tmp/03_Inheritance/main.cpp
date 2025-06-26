#include<iostream>
using namespace std;
/*
    一.继承方式
        继承方式        基类 public 成员	基类 protected 成员	    基类 private 成员
        public 继承     仍然是 public	    仍然是 protected	    无法访问
        protected 继承	变成 protected	    仍然是 protected	    无法访问
        private 继承	变成 private	    变成 private	        无法访问
    二.构造函数与析构函数
        派生类不会继承基类的构造函数，但会调用基类构造函数。
        构造顺序：基类构造函数 先执行，派生类构造函数 后执行。
        析构顺序：派生类析构函数 先执行，基类析构函数 后执行（先构造后析构）
*/
class Base {
public:
    Base() { cout << "Base Constructor" << endl; }
    ~Base() { cout << "Base Destructor" << endl; }
};
    
class Derived : public Base {
public:
    Derived() { cout << "Derived Constructor" << endl; }
    ~Derived() { cout << "Derived Destructor" << endl; }
};
/*
    三.多继承与菱形继承
        1.C++ 支持多继承，即一个类可以继承多个基类,如果两个基类有相同的成员函数，派生类必须明确指明调用哪个基类的函数.
        2.虚继承（避免菱形继承问题）
                class A {
                public:
                    void show() { cout << "A::show()" << endl; }
                };

                class B : public A {};
                class C : public A {};
                class D : public B, public C {}; // 菱形继承
            D 继承了 B 和 C，而 B 和 C 又继承自 A，导致 D 拥有两个 A 的拷贝。这可能导致数据冗余和二义性问题。
*/

class A {
public:
    void show() { cout << "A::show()" << endl; }
};

class B : virtual public A {};
class C : virtual public A {};
class D : public B, public C {};


int main(){
    //继承后构造函数与析构函数执行顺序：父类构造->子类构造; 子类析构->父类析构
    Derived dd;


    //棱形继承
    D obj;
    obj.show();

    return 0;
}