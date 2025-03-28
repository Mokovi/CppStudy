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
