#include <iostream> 

/*
1. RAII
    RAII（Resource Acquisition Is Initialization，资源获取即初始化）是一种利用对象生命周期管理资源的核心编程范式.
    1） 核心思想:
        资源获取：在对象构造函数中获取资源。
        资源释放：在对象析构函数中释放资源。
        核心目标：确保资源始终被正确释放，即使发生异常。
    2） 常见RAII应用场景
        内存管理：std::unique_ptr, std::shared_ptr, std::vector。
        文件操作：std::fstream, std::ifstream。
        锁管理：std::lock_guard, std::unique_lock。
        网络连接：封装数据库连接、Socket 连接。
        图形资源：OpenGL 纹理、缓冲区对象。
*/

/*
2. 智能指针
    1） std::unique_ptr
        特点
            独占所有权：同一时刻只有一个 unique_ptr 能管理一个资源。
            不可复制，但可移动：unique_ptr 的拷贝构造函数和复制赋值操作符均被删除，只有通过 std::move() 才能转移所有权。
            零开销：通常其内部仅保存一个原始指针，体积与普通指针相当。
        使用场景
            当资源只需单个所有者时，使用 unique_ptr 可获得最佳性能与最简单的所有权管理。
            可作为函数返回值传递资源所有权，充分利用移动语义。
    2） std::shared_ptr
        特点
            共享所有权：多个 shared_ptr 对象可以共同拥有同一资源，内部通过引用计数管理。
            自动释放：当引用计数归零时，自动调用 delete 释放资源。
            支持跨函数、跨容器传递：便于在复杂项目中共享资源，但需要注意循环引用问题。
        使用场景:
            多个模块或对象需要访问同一个资源时，例如图形应用中多个控件共享同一纹理。
            动态数据结构（如图、树）的节点可能会被多个父节点引用时。
            跨线程共享资源，确保在任何线程中资源不会被提前销毁（注意引用计数本身是线程安全的，但访问资源的操作仍需要额外保护）。
        补充：
                std::shared_ptr 可以通过 get() 方法来获取原始指针，通过 reset() 来减少一个引用计数，并通过use_count()来查看一个对象的引用计数
                每次创建 shared_ptr，引用计数增加 1。
                每次 shared_ptr 复制，引用计数增加 1。
                当 shared_ptr 释放（超出作用域或调用 reset()），引用计数减少 1。
                当引用计数降到 0，shared_ptr 自动释放资源。

    3） std::weak_ptr
        特点:
            弱引用：weak_ptr 不参与引用计数，不改变 shared_ptr 管理资源的生命周期。
            解决循环引用：在两个或多个对象间互相引用时，用 weak_ptr 替换其中至少一个引用，可以打破循环，确保资源能正常释放。
            访问资源需先 lock()：由于 weak_ptr 自身不能直接解引用，需调用 lock() 得到 shared_ptr 后再使用。
        使用场景:
            当一个对象仅需要观察资源状态而不控制其生命周期时，如缓存机制中检查资源是否仍然存在。
            解决 shared_ptr 之间的循环引用问题。例如，父子对象互相引用时，将其中一个改为 weak_ptr。
*/
#include <memory> 
class MyClass {
public:
    MyClass() { std::cout << "MyClass 构造\n"; }
    ~MyClass() { std::cout << "MyClass 析构\n"; }
    void show() { std::cout << "调用 MyClass::show()\n"; }
};
void testUniquePtr(){
     // 使用 make_unique 创建 unique_ptr（C++14 及以上）
    std::unique_ptr<MyClass> uptr1 = std::make_unique<MyClass>();
    uptr1->show();
 
     // 转移所有权（移动语义）
     std::unique_ptr<MyClass> uptr2 = std::move(uptr1);
     uptr2->show();
     // 当 uptr2 离开作用域时自动释放内存
}
void testSharedPtr(){
    std::shared_ptr<MyClass> sptr1 = std::make_shared<MyClass>();
    std::cout << "sptr1 use count: " << sptr1.use_count() << std::endl;
    {
        std::shared_ptr<MyClass> sptr2 = sptr1;
        std::cout << "sptr2 use count: " << sptr2.use_count() << std::endl;
    }
    std::cout << "sptr1 use count: " << sptr1.use_count() << std::endl;
}

class Parent;
class Child;

class Parent {
public:
    ~Parent() { std::cout << "Parent 析构\n"; }
    // 用 weak_ptr 避免循环引用
    std::weak_ptr<Child> child_ptr;
};

class Child {
public:
    ~Child() { std::cout << "Child 析构\n"; }
    std::weak_ptr<Parent> parent_ptr;
};
void testWeakPtr(){
    std::shared_ptr<Parent> parent = std::make_shared<Parent>();
    std::shared_ptr<Child> child = std::make_shared<Child>();

    parent->child_ptr = child;
    child->parent_ptr = parent;

    std::cout << "Parent use_count: " << parent.use_count() << "\n"; // 输出1
    std::cout << "Child use_count: " << child.use_count() << "\n";   // 输出1

    // 当 parent 和 child 离开作用域时，由于 weak_ptr 不增加引用计数，
    // 两个对象都能正常析构，避免了循环引用问题
}



int main(){

    testUniquePtr();
    testSharedPtr();
    testWeakPtr();
    return 0;
}