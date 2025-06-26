#include <iostream>
/*
1. static_cast
    用途：编译时已知的类型转换（无运行时检查）。
    适用场景：
        基础类型之间的转换（如 int → double）。
        类层次中的向上转换（派生类指针→基类指针）。
        无继承关系的指针转换（需用户保证安全）。
        new_type variable = static_cast<new_type>(expression);
2. dynamic_cast
    用途：类层次间的安全向下转换和侧向转换（在同一继承体系中的不同派生类之间转换）（运行时检查）。
    要求：目标类必须有虚函数（多态类型）。
    结果：
        成功：返回目标类型指针/引用。
        失败：指针返回 nullptr，引用抛出 std::bad_cast。
        Derived* dp = dynamic_cast<Derived*>(basePtr);
3. const_cast
    用于添加或移除变量的 const 或 volatile 限定符。它只能用于指针或引用，不能直接用于非指针或非引用变量。
        const T* cp = &value;
        T* p = const_cast<T*>(cp);  // 移除 const 限定
4. reinterpret_cast
    用于在不相关的指针类型之间、指针和整数之间进行转换，其本质是重新解释表达式的比特模式。语法为
        new_type variable = reinterpret_cast<new_type>(expression);


转换方式	        安全性	        适用场景	                   检查时机
static_cast	        中	        明确的类型转换（基础类型、类层次）	 编译时
dynamic_cast	    高	        多态类层次的安全向下转换	        运行时
const_cast	        低	        修改 const/volatile	              编译时
reinterpret_cast	极低	    底层二进制数据重新解释	            编译时
*/

class Base { virtual void foo() {} };
class Derived : public Base {};
class Derived2 : public Base {};

int main(){
    double num = static_cast<double>(10);
    std::cout << "Static casted number: " << num << std::endl;

    Base* base = new Derived();
    Derived* derived = dynamic_cast<Derived*>(base);  // 安全转换
    Derived2* derived2 = dynamic_cast<Derived2*>(derived);  // 安全转换

    const int x = 10;
    int* p = const_cast<int*>(&x);  // 移除 const
    *p = 20;  // 未定义行为！x 原本是 const
    std::cout << "Modified x: " << *p << std::endl;

    float f = 3.14f;
    int i = reinterpret_cast<int&>(f);  // 获取浮点数的二进制表示
    std::cout << "Reinterpreted int: " << i << std::endl;
    delete base;  // 清理动态分配的内存

    return 0;
}

