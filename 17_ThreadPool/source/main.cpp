#include <iostream>
#include <vector>
#include <numeric>   // std::accumulate
#include "threadPool.h" // 假设上面线程池实现放在这个头文件中

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
    const size_t dataSize = 1000000;
    std::vector<int> data(dataSize);
    for (size_t i = 0; i < dataSize; ++i) {
        data[i] = i % 100;
    }

    // 创建线程池（例如 4 个线程）
    ThreadPool pool(4);

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
    std::cout << "数组的平方和为: " << totalSum << std::endl;

    // 关闭线程池（析构时自动调用）
    return 0;
}
