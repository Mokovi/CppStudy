/*
一、#pragma
    1. 防止头文件重复包含
        // 替代传统的 #ifndef/#define 宏
        #pragma once  
        // 告诉编译器此头文件只需包含一次（现代编译器广泛支持，但非 C/C++ 标准）
    2. 指定结构体对齐方式
        #pragma pack(push, 1)  // 保存当前对齐方式，设置 1 字节对齐（无填充）
        struct MyStruct {
            char a;
            int b;
            double c;
        };
        #pragma pack(pop)       // 恢复之前的对齐方式
    3.  禁用/启用编译器警告
        #pragma warning(disable : 4996)  // 禁用 MSVC 的 "不安全函数" 警告（如 scanf）
        #pragma warning(push)            // 保存当前警告状态
        #pragma warning(disable : 4244)  // 禁用特定警告（如类型转换丢失数据）
        // ... 代码 ...
        #pragma warning(pop)             // 恢复之前的警告状态
    4. OpenMP 并行编程
        #include <omp.h>
        #pragma omp parallel for  // 启用 OpenMP 并行化 for 循环
        for (int i = 0; i < 100; i++) {
            // 并行执行的代码
        }
    5. 代码区域标记
        a. 代码段折叠（IDE 支持）
            #pragma region MyCodeSection
            // ... 代码 ...
            #pragma endregion
        b. 标记未实现代码
            #pragma message("TODO: Implement this function!")
            void placeholder() {}
*/
#include <iostream>

#pragma pack(push, 1)  // 保存当前对齐方式，设置 1 字节对齐（无填充）
struct MyStruct {
    char a;
    int b;
    double c;
};
#pragma pack(pop)       // 恢复之前的对齐方式

struct MyStruct2 {
    char a;
    int b;
    double c;
};

void test(){
    std::cout << "Mystruct size :" << sizeof(MyStruct) << std::endl;
    std::cout << "Mystruct2 size :" << sizeof(MyStruct2) << std::endl;
}

/*
二、C++ <chrono> 库
1. 核心组件
    1) 时间段（std::chrono::duration）
        表示时间间隔，由 数值（计数） 和 单位（比例） 组成。
                template<class Rep, class Period = std::ratio<1>>
                class duration;
            Rep：数值类型（如 int64_t、double）。
            Period：单位比例，默认秒（std::ratio<1>），如 std::milli 表示毫秒（1/1000）。
        e.g.
            auto t1 = 100ms;    // 100 毫秒（C++14 起支持字面量）
            auto t2 = 2h + 30min; // 时间段可直接运算
    2) 时间点（std::chrono::time_point）
        表示某一时钟的特定时间点，由 时钟（Clock） 和 时间段（Duration） 组成。
                template<class Clock, class Duration = typename Clock::duration>
                class time_point;
        e.g.
            auto now = Clock::now();       // 获取当前时间点
            auto elapsed = now - prevTime; // 计算时间间隔（返回 duration）
    3) 时钟（Clocks）
            时钟类型	特性
            system_clock	系统范围的实时时钟，可转换为日历时间（如 std::time_t）。
            steady_clock	单调递增时钟，适合测量时间间隔（不受系统时间调整影响）。
            high_resolution_clock	最高精度的时钟（通常是 steady_clock 的别名）。
        e.g. 
            auto start = std::chrono::steady_clock::now(); // 开始时间点
            // ... 执行代码 ...
            auto end = std::chrono::steady_clock::now();   // 结束时间点
            auto duration = end - start;                   // 计算时间间隔
2. 常用函数
    1) 时间转换函数
        duration_cast：安全转换时间段单位(会损失精度，直接丢去小数部分）。
            auto ms = 1500ms;
            auto sec = std::chrono::duration_cast<std::chrono::seconds>(ms); // 1s（截断500ms）
        time_point_cast：转换时间点的单位。
            auto now = system_clock::now();
            auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    2) 与 C 时间类型的互转
        system_clock 与 time_t：
            auto now = std::chrono::system_clock::now();
            std::time_t t = std::chrono::system_clock::to_time_t(now); // 转 time_t
            auto tp = std::chrono::system_clock::from_time_t(t);       // 转 time_point
        格式化输出时间：
            #include <iomanip>
            std::time_t t = system_clock::to_time_t(now);
            std::cout << std::put_time(std::localtime(&t), "%F %T"); // 输出 "2025-04-12 13:30:00"
    3) 时间字面量（C++14 起）
            using namespace std::chrono_literals;
            auto t1 = 100ms;    // 100 毫秒
            auto t2 = 5min;     // 5 分钟
            auto t3 = 2h + 30s; // 2 小时 30 秒
*/
//测试代码执行时间
#include <chrono>
#include <thread>
void timeConsumingTask() {
    // 模拟耗时操作
    std::this_thread::sleep_for(std::chrono::milliseconds(600));
}

void computeTime() {
    auto start = std::chrono::steady_clock::now();
    timeConsumingTask();
    auto end = std::chrono::steady_clock::now();
    auto duration = end - start;

    std::cout << "Time elapsed: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count()
              << "ms\n";
}
// 定时器与超时控制
#include <atomic>
using namespace std::chrono_literals;
std::atomic<bool> taskDone(false);
void sideThread(){
    std::this_thread::sleep_for(5s); // 模拟工作
    taskDone = true;
}

void testOvertime(){
    std::thread t(sideThread);
    auto timeout = 3s;
    if(!taskDone){
        auto start = std::chrono::steady_clock::now();
        while(!taskDone) {
            if (std::chrono::steady_clock::now() - start > timeout) {
                std::cout << "Timeout!\n";
                break;
            }
            std::this_thread::sleep_for(100ms);
        }
    }
    t.join();
}
/*
三、namespace
1. 基本概念
    命名空间旨在解决名称冲突问题。在大型项目中，可能会出现不同模块定义了同名的函数、类或变量。将它们放在不同的命名空间中，可以避免互相干扰。
    语法结构：
        命名空间使用关键字 namespace 定义，定义体内的所有标识符都会属于该命名空间。例如：
            namespace MyNamespace {
                int value = 42;
                void printValue() {
                    std::cout << "value: " << value << std::endl;
                }
            }
2. using
    为了减少每次使用命名空间成员时都写前缀，可以通过两种方式进行引入：
        只将命名空间中的特定名称引入当前作用域。
            using MyNamespace::value;
            using MyNamespace::printValue;
        将整个命名空间引入当前作用域，使得该命名空间中的所有名称都可以直接使用。
            using namespace MyNamespace;
3. 嵌套命名空间
    命名空间可以嵌套使用，从而形成层次结构，有助于进一步组织代码。
4. 匿名命名空间
    匿名命名空间（unnamed namespace）没有名字，其内部声明的标识符仅在当前翻译单元（源文件）中可见，相当于使用了 static 限定符
    匿名命名空间常用于防止名称污染，确保全局标识符仅对单个源文件可见。
        namespace {
            int internalValue = 100;
            void internalFunction() {
                std::cout << "内部函数" << std::endl;
            }
        }

        int main() {
            internalFunction();
            std::cout << internalValue << std::endl;
            return 0;
        }
5. 综合
        在大型项目中，不同模块的代码通常分别放置在各自的命名空间内。这样不仅有助于避免命名冲突，还可以清晰地表达模块间的层次和关系。
    例如，在一个项目中，可以将核心库、界面库和工具库分别放入不同的命名空间中。

    namespace Core {
        class Engine {
        public:
            void run() {
                std::cout << "Engine running" << std::endl;
            }
        };
    }

    namespace UI {
        class Window {
        public:
            void show() {
                std::cout << "Window shown" << std::endl;
            }
        };
    }

    namespace Utils {
        void log(const std::string& msg) {
            std::cout << "[LOG]: " << msg << std::endl;
        }
    }

    int main() {
        Core::Engine engine;
        engine.run();

        UI::Window window;
        window.show();

        Utils::log("Application started");
        return 0;
    }
*/


int main(){
    //test();
    //computeTime();
    testOvertime();
    return 0;
}

