#include<iostream>
/*
一、内存分区模型概述:
程序运行前：在程序编译后，生成了可执行程序代码，未执行该程序前
    1.代码区：存放程序的二进制代码，由操作系统进行管理
        存放 CPU 执行的机器指令
        代码区是共享的，对于频繁被执行的程序，只需要在内存中有一份代码即可
        代码区是只读的，防止程序意外修改它的指令
    2.全局/静态区：存放全局变量和静态变量以及字符串字面量。,该区域的数据在程序结束后由操作系统释放
        又分为:
            BSS 段（未初始化的全局变量和静态变量，程序运行时初始化为 0）
            Data 段（已初始化的全局变量和静态变量）
程序运行后：
    3.栈区：由系统自动分配释放, 存放函数的参数、局部变量、返回值等； LIFO； 运行最快，但空间较小（通常 1MB 左右，具体取决于系统和编译器）
    4.堆区：由程序员分配和释放,若程序员不释放,程序结束时由操作系统回收
注意：并不是所有的常量都存储在全局区.
*/
// 全局变量：
// global_initialized 存放在 Data 段（已初始化的全局变量）
// global_uninitialized 存放在 BSS 段（未初始化的全局变量，程序运行时初始化为 0）
int global_initialized = 42;
int global_uninitialized;

// 全局字符串字面量：
// "Hello, World!" 通常存储在只读数据区（常量区）
// 注意：并非所有常量都一定存放在全局区，编译器可能根据优化策略存放在其它区域。
const char* global_string_literal = "Hello, World!";

// 一个普通函数，其代码存放在代码区（Text Segment），该区域只读且共享
void memoryInfo() {
    // 局部变量：存储在栈区（Stack），自动分配和释放
    int localVar = 10;
    // 静态局部变量：存储在全局/静态区（Data 或 BSS 段），生命周期贯穿程序始终
    static int staticLocal = 20;
    // 动态分配的变量：存储在堆区（Heap），由程序员分配和释放
    int* heapVar = new int(30);
    // 局部常量：存放位置依编译器优化，通常在栈上或直接内嵌到代码中
    const int constLocal = 100;
    std::cout << "---- 内存分区信息 ----" << std::endl;
    // 打印函数地址，代码区只读区域
    std::cout << "memoryInfo() 函数地址（代码区）： " << (void*)memoryInfo << std::endl;
    // 全局变量地址
    std::cout << "global_initialized 地址（Data 段）： " << (void*)&global_initialized << std::endl;
    std::cout << "global_uninitialized 地址（BSS 段）： " << (void*)&global_uninitialized << std::endl;
    // 字符串字面量地址（常量区/只读数据区）
    std::cout << "global_string_literal 指向的地址（常量/只读区）： " << (void*)global_string_literal << std::endl;
    // 局部变量地址（栈区）
    std::cout << "localVar 地址（栈）： " << (void*)&localVar << std::endl;
    // 静态局部变量地址（全局/静态区）
    std::cout << "staticLocal 地址（全局/静态区）： " << (void*)&staticLocal << std::endl;
    // 堆内存地址（堆区）
    std::cout << "heapVar 地址（堆）： " << (void*)heapVar << std::endl;
    // 局部常量地址（通常在栈上，但编译器可能优化掉） 
    std::cout << "constLocal 地址（常量，可能在栈）： " << (void*)&constLocal << std::endl;
    // 释放堆内存
    delete heapVar;
}


/*
二、引用
    什么是引用：引用是一种取别名的机制;其本质在c++内部实现是一个指针常量,但是所有的指针操作编译器都帮我们做了
    什么情况下适合用引用：
        1、跨函数共享变量时，引用比指针安全(不存在空引用、极少出现野引用)、引用比指针更方便(不用取地址、解引用)
        2、提高传参效率，引用的传参效率比指针还高，因为指针还需要4\8字节用于存储内存地址，而引用一个字节都不需要，但是引用与指针一样有被修改的风险，因此为了安全需要加const保护一下
    重点：指针与引用的相同点和不同点：
        相同点：
            都可以跨函数共享变量、都可以提高函数传参效率、也都需要const保护
        不同点：
            1、引用是一种取别名的机制，指针是一种数据类型
            2、引用不需要额外的存储空间，而指针需要4\8字节内存用于存储内存地址编号。虽然引用本质上是常量指针，但编译器通常会直接替换引用为原变量的地址访问，避免额外存储。
            3、引用不能更换指向目标，而指针可以更改指向
            4、引用必须初始化，而指针可以不初始化
            5、有空指针，但没有空引用
            6、指针可以配合堆内存使用，引用不可以
    
    使用引用时需要注意的问题：
        1、引用必须初始化、不存在空的引用
        2、可以引用右值，但必须使用const修饰
        3、引用不可以修改目标
        4、函数返回引用类型的数据时，不要返回局部变量的引用
*/
//1.引用作为函数参数
void swap(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
}
void testSwap(){
    int a = 10;
    int b = 20;
    std::cout << "a = " << a <<"\t b = " << b << std::endl;
    swap(a,b);
    std::cout << "a = " << a <<"\t b = " << b << std::endl;
}
//2.引用作为函数返回值
int& returnValue(){
    static int a = 100; //不能返回局部变量
    return a;
}
void testReturnValue(){
    int& a = returnValue();
    std::cout << "a = " << a <<std::endl;
    returnValue() = 1000; //引用也可用于左值
    std::cout << "a = " << a <<std::endl;
}
//3.常量引用
void testConstValue()
{
    //int& a = 10; 报错，引用必须是一个合法的空间
    const int&a = 10;
    //a = 20; 报错, 加入const后，a的指向，内容都无法修改.
    
}

int main(){
    memoryInfo();
    testSwap();
    testReturnValue();
    return 0;
}
