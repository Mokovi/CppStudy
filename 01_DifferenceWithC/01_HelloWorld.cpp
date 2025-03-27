#include <iostream>
#include <cstring>
#include <string>
#include <new>
/*
1、结构体的不同
        a、不再需要typedef关键字进行省略struct，在设计好结构后，定义结构变量时不再需要struct关键字
        b、结构中的结构成员可以是成员变量还可以是成员函数，结构变量、结构指针分别使用 . 或 -> 访问成员函数，在成员函数中可以直接访问本结构的其它成员变量、成员函数，不再需要 . ->
        c、结构中有一些隐藏的成员函数(构造、析构、拷贝构造、赋值函数)
        d、可以给结构成员设置访问属性
            public          公开    (默认)
            protected       保护的
            private         私有的
        e、结构是可以继承其它结构、也可以被其他结构继承

C++ 中 类（class） 和 结构体（struct） 的主要区别如下：
    默认权限不同
        struct 的成员默认是 public, struct 继承时，默认是 public 继承。
        class 的成员默认是 private, class 继承时，默认是 private 继承。
    在 C++ 中，struct 和 class 其实是一样的，可以定义成员变量、成员函数、构造函数、析构函数、继承、多态等，唯一的主要区别就是默认访问权限不同。
    struct 更适合用于简单的数据存储，比如 Point、Color、Vector3D，主要用于封装一组数据。class 更适合面向对象编程，封装数据和行为，通常用于更复杂的对象建模。
*/
struct Person{
    std::string name;
    int age;

    void introduce(){
        std::cout << "My name is " << name << ", and my age is " << age << std::endl; 
    }
};

struct Employee : public Person
{
    int salary;
    void work(){
        std::cout << name << "is working and earns " << salary << "yuan!" << std::endl;
    }
};
// 2. 联合体的不同，与结构体前四点相同.
union Data {
    int intValue;
    float floatValue;
    char str[20];
    
    void printInt() { std::cout << "Int: " << intValue << std::endl; }
    void printFloat() { std::cout << "Float: " << floatValue << std::endl; }
};
/*
 3、枚举的不同
        a、不再需要typedef关键字进行省略enum，在设计好枚举后，定义枚举变量时不再需要enum关键字
        b、是一种独立的数据类型，不能与整形进行自动隐式转换
*/
enum Color {
    RED,
    GREEN,
    BLUE
};
/*
4、bool类型的不同
        a、C++中有真正的布尔类型，bool是C++中的关键字，不需要包含stdbool.h可直接使用
        b、true、false 也是C++中的关键字，但在C语言中都不是
        c、true、false 在C++中是1字节，而在C中是4字节，在C中是宏
        注意：无论是C还是C++中bool类型都是1字节，且只存储0|1
*/
void boolDemo() {
    bool flag = true;
    std::cout << "Boolean value: " << flag << std::endl;
}

/*
   5、字符串的不同
        a、C++中的字符串封装成了string类，但还可以使用C中的字符串，且能与string进行相互转换
        b、string类型被封装在string头文件，但已经被包含到iostream中，属于std名字空间
        c、可以使用string字符串成员函数、还可以使用运算符的方式操作string类，但是C语言中的string.h系列函数还可以继续使用
            =   strcpy
            +=  strcat
            ==  strcmp
            .size() strlen 
            .c_str()    由string转换为char*
        d、C++中没有规定string必须以'\0'为结束标志，编译器可能在末尾加，也可能不加，由编译器决定，因为它的长度信息封装到类的私有成员中
*/
void stringDemo() {
    std::string cppStr = "Hello, C++!";
    const char* cStr = cppStr.c_str();
    std::cout << "C++ String: " << cppStr << std::endl;
    std::cout << "Converted to C string: " << cStr << std::endl;
    
    char oldCStr[20] = "C Style";
    std::string newCppStr = oldCStr;
    std::cout << "Converted to C++ string: " << newCppStr << std::endl;
}
/*
    6. C++的堆内存管理
        a.C++中有专门管理堆内存的语句，而C语言只能标准库中的函数
            new     分配堆内存  相当于C语言中的malloc
            delete  释放堆内存  相当于C语言中的free
        b.new分配内存时可以直接对内存进行初始化
             类型* p = new 类型(初始值);
        c.使用new分配内存时会自动调用结构、联合、类类型的构造函数，而使用delete会自动调用这些类型的析构函数，但是malloc\free并不会调用构造、析构函数
        d.数组的分配和释放
            类型* p = new 类型[数量];
            相当于分配连续的多块相同类型的内存，类似于C中的calloc
            delete[] 专门用于释放通过new[]方式所申请的内存，并且它会自动多次调用析构函数
            使用new[]为结构、联合、类申请到的内存前4/8个字节(32位系统是4，64位系统是8)记录了申请的次数，这样的目的是为了让编译器在delete[]知道应该调用多少次析构函数
        e.new分配失败则会抛出一个异常     std::bad_array_new_length
        f.使用delete后最好将指针指向nullptr
            推荐 delete 后置 nullptr，避免悬空指针，特别是在长生命周期的指针变量中。
            如果指针生命周期短（如局部变量），则不必显式置 nullptr。
            使用智能指针（std::unique_ptr、std::shared_ptr）避免手动管理内存，从根本上杜绝此类问题。
*/

class Human{
public:
    Human(const std::string& name, int age):name(name), age(age){
        std::cout << "Huamn Constructor "<< name << " has created." <<std::endl;
    }
    ~Human(){
        std::cout << "Huamn Destructor "<< name << " has destroyed." <<std::endl;
    }
    void introduce(){
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
private:
    std::string name;
    int age;
};

void heapMemoryManagement() {
    try {
        // a. 使用 new 和 delete 分配/释放单个对象
        Human* p1 = new Human("Alice", 25);
        p1->introduce();
        delete p1; // 自动调用析构函数
        
        // b. 直接初始化
        int* intPtr = new int(42); //使用小括号，直接初始化
        std::cout << "Allocated int: " << *intPtr << std::endl;
        delete intPtr;
        
        // c. new/delete 调用构造、析构函数
        Human* p2 = new Human("Bob", 30);
        delete p2; 
        
        // d. new[] 和 delete[] 分配/释放数组
        Human* people = new Human[3]{
            {"Charlie", 20},
            {"David", 35},
            {"Eve", 40}
        };
        delete[] people; // 依次调用析构函数
        
        // e. new 分配失败的异常捕获
        try {
            int* largeArray = new int[999999999999]; // 可能导致 bad_alloc
            delete[] largeArray;
        } catch (const std::bad_alloc& e) {
            std::cerr << "Memory allocation failed: " << e.what() << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}


int main()
{
    /*
    // 结构体测试
    Employee emp;
    emp.name = "Alice";
    emp.age = 30;
    emp.salary = 5000;
    emp.introduce();
    emp.work();
    
    // 联合测试
    Data data;
    data.intValue = 42;
    data.printInt();
    
    // 枚举测试
    Color favoriteColor = BLUE;
    //Color favoriteColor = 0;  这样写会报错
    std::cout << "Favorite color: " << favoriteColor << std::endl;
    
    // bool 测试
    boolDemo();
    
    // 字符串测试
    stringDemo();
    */

    //测试堆
    //heapMemoryManagement();

    std::cout << "Sizeof Bool is " << sizeof(bool) << " Byte." <<std::endl;

    return 0;
}