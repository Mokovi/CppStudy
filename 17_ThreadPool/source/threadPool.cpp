#include "threadPool.h"


ThreadPool::ThreadPool(size_t size) : stop(false){
    for(int i = 0; i < size; i++){
        workers.emplace_back(&ThreadPool::worker, this);
        /*
            worker不是没有形参嘛，this的作用是什么？
                虽然 worker() 是一个没有显式形参的成员函数，但它是一个非静态成员函数，需要一个实例来调用。
            当使用成员函数指针调用非静态成员函数时，第一个参数必须是对象指针，即用来指定调用该成员函数的对象。
        */
    }
}

void ThreadPool::worker(){
    while(true){
        std::function<void()> task;
        {
            // 取任务时加锁，直到有任务或线程池停止
            std::unique_lock<std::mutex> lock(queueMutex);
            condition.wait(lock, [this](){return stop || !tasks.empty();});
            if (stop && tasks.empty())
                return;
            task = std::move(tasks.front());
            tasks.pop();
        }
        task();
    }
}

ThreadPool::~ThreadPool(){
    shutdown();
}

void ThreadPool::shutdown(){
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        stop = true;
        /*
            stop 是 atomic，但为什么还需要锁？
            1. stop 是原子变量，仅保证自身的原子性，但线程池中还有任务队列（tasks）和其他状态信息需要同步访问。锁（queueMutex）确保在修改这些相关数据时具备一致性和互斥性。
            2. 条件变量的等待机制依赖于与之关联的互斥锁来保证等待条件的正确检查和唤醒。通过锁定 queueMutex，可以确保设置 stop 后，所有等待线程能看到最新状态并正确退出。
        */
    }
    condition.notify_all();
    for(auto& worker : workers){
        if(worker.joinable())
            worker.join();
    }
}



