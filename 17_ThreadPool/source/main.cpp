#include <iostream>
#include <vector>
#include <numeric>   // std::accumulate
#include "threadPool.h" // 假设上面线程池实现放在这个头文件中
#include <chrono>

// 计算数组一部分的平方和
long long partialSum(const std::vector<int>& data, size_t start, size_t end) {
    long long sum = 0;
    for (size_t i = start; i < end; ++i) {
        sum += static_cast<long long>(data[i]) * data[i];
    }
    return sum;
}

int main() {
    // 构造一个大数组
    const size_t dataSize = 10000000;
    std::vector<int> data(dataSize);
    for (size_t i = 0; i < dataSize; ++i) {
        data[i] = i % 100;
    }
    // 单线程计算
    auto start1 = std::chrono::high_resolution_clock::now();
    long long res1 = partialSum(std::cref(data), 0, dataSize);
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration1 = end1 - start1;
    std::cout <<"[串行] 计算结果: "<< res1 <<", 总耗时: " << duration1.count() << " 秒.\n";

    // 多线程计算
    // 创建线程池
    auto start2 = std::chrono::high_resolution_clock::now();
    /*
     关于线程数选择:
        1. CPU 密集型任务（如计算、图像处理、数据压缩等）
            建议线程数量 ≈ CPU 核心数;
            原因：这种任务几乎不阻塞，主要消耗 CPU，线程多了会导致频繁切换。
        2. IO 密集型任务（如网络、磁盘、数据库访问等)
            建议线程数量 ≈ CPU 核心数 × 2～4
            原因：IO 操作时线程常常阻塞，线程可以多一些以利用 CPU 空闲时间。
        3. 总结:
                场景	        建议线程数
            CPU 密集型	std::thread::hardware_concurrency()
            IO 密集型	2 × std::thread::hardware_concurrency() 或更多
            混合型	    介于两者之间，可根据任务占比调试
            自适应	    根据任务队列长度动态调整（高级实现）
        std::thread::hardware_concurrency() 会返回当前机器的逻辑CPU核心数。
    */
    //ThreadPool pool(4);
    ThreadPool pool(std::thread::hardware_concurrency());
    // 将数据分成若干块，每块任务计算局部平方和
    const size_t blockSize = dataSize / 4;
    std::vector<std::future<long long>> futures;
    for (size_t i = 0; i < 4; ++i) {
        size_t start = i * blockSize;
        size_t end = (i == 3) ? dataSize : (start + blockSize);
        futures.push_back(pool.enqueue(partialSum, std::cref(data), start, end));
        /*
            这里std::cref的作用？
                std::cref 的作用是将一个对象包装为“常量引用”，以便在多线程或异步任务中安全地传递引用参数。
                data 是一个容器（比如 std::vector），你希望把它作为常量引用传递给 partialSum 函数。
                直接传递 data，enqueue 可能会把它拷贝一份（变成值传递），这样效率低下，且不是你想要的效果。
                用 std::ref(data) 或 std::cref(data) 可以把 data 包装成引用传递，但 std::ref 是非常量引用，std::cref 是常量引用。
        */
    }

    // 累加各个块的结果
    long long totalSum = 0;
    for (auto& fut : futures) {
        totalSum += fut.get();
    }
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration2 = end2 - start2;
    std::cout <<"[并行] 计算结果: "<< totalSum <<", 总耗时: " << duration2.count() << " 秒.\n";

    // 关闭线程池（析构时自动调用）
    return 0;
}
