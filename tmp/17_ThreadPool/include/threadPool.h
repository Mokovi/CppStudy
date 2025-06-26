#ifndef __THREADPOOL__H__
#define __THREADPOOL__H__

#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <atomic>

class ThreadPool {
public:
    ThreadPool(size_t threadCount);
    ~ThreadPool();

    // 提交任务到线程池，返回一个future用于获取任务返回值
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) 
        -> std::future<typename std::result_of<F(Args...)>::type>;
    /*
        分段解释一下语法：
            1. F&& f, Args&&... args
                这是完美转发的参数声明，意思是：
                    F&& f：以“转发引用（universal reference）”方式接收任务函数。
                    Args&&... args：同样是转发引用，用于接收任务的参数。
                    搭配 std::forward 使用，可以保持传入函数及参数的原始左值/右值特性，避免多次拷贝。
            2. auto ... -> std::future<...> 尾返回类型
            3. std::result_of<F(Args...)>::type 
                这是 类型萃取（type traits） 技术：
                    std::result_of<F(Args...)>::type 表示调用 F(args...) 后的返回类型。
                    举例：如果 F = int(int, int)，Args 是两个 int，那么这个表达式就是 int。
            4. typename 
                    因为 F 和 Args... 是模板参数，std::result_of<F(Args...)> 是依赖于模板参数的 依赖类型（dependent type），
                那么你必须加上 typename 告诉编译器 “我知道这后面是一个类型”
            5. 新的写法：
                c++17: 
                    1. template<class F, class... Args>
                        auto enqueue(F&& f, Args&&... args)
                            -> std::future<decltype(f(args...))>
                    2. template<class F, class... Args>
                        auto enqueue(F&& f, Args&&... args) {
                            using return_type = decltype(f(args...));
                            std::packaged_task<return_type()> task(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
                            // ...
                        }
    */

    // 关闭线程池，等待所有线程结束
    void shutdown();

private:
    // 工作线程函数，不断从任务队列中取任务执行
    void worker();

    // 线程池内部变量
    std::vector<std::thread> workers;                    // 工作线程集合
    std::queue<std::function<void()>> tasks;             // 任务队列

    std::mutex queueMutex;                               // 保护任务队列的互斥锁
    std::condition_variable condition;                   // 条件变量用于唤醒工作线程
    std::atomic<bool> stop;                              // 是否停止线程池
};

/*
注意：
    模板函数必须在编译时可见，通常需要将其定义写在头文件中（或者在同一个翻译单元内）。
    如果你把 ThreadPool::enqueue 的实现放在了 .cpp 文件中，链接器在实例化模板时就找不到相应定义，从而导致“undefined reference”错误。
*/


template<class F, class... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args) 
    -> std::future<typename std::result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type;

    // 封装任务为 packaged_task
    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );
    /*
        std::packaged_task<R()> 封装一个可调用对象，其调用签名为 R()（无参数，返回 R）。（std::packaged_task可以封装其他类型啊，别误解了）
        std::bind 用于绑定一个函数和它的参数，将原本形如 R(Args...) 的函数转换为一个没有参数的函数对象（即 R()），这样它就符合 std::packaged_task 的要求
        std::forward：用于实现完美转发，确保函数 f 和参数 args... 在转发到 std::bind 时保持它们的原始值类别（左值或右值），避免不必要的拷贝或错误的引用语义。
        std::make_shared<>(std::bind(std::forward<F>(f), std::forward<Args>(args)...)) 将std::bind(std::forward<F>(f), std::forward<Args>(args)...)作为参数传给std::packaged_task的构造函数
    */

    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        // 不允许在关闭后添加新任务
        if (stop)
            throw std::runtime_error("enqueue on stopped ThreadPool");
        tasks.emplace([task](){ (*task)(); });
    }
    condition.notify_one();
    return res;
}

#endif