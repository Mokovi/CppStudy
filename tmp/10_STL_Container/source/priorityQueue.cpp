/*
priority_queue
    优先队列，基于堆实现，元素按优先级排序。
    适用场景：需要按优先级处理元素，如任务调度。
*/

#include <iostream>
#include <queue>


//std::priority_queue 常用于实现 Dijkstra 算法，用于求解单源最短路径。


int main() {

    //创建
    // 创建一个空的 priority_queue（默认是最大堆）
    std::priority_queue<int> pq1;
    // 使用 vector 初始化 priority_queue
    std::vector<int> vec = {3, 1, 4, 1, 5, 9};
    std::priority_queue<int> pq2(vec.begin(), vec.end());
    // 输出 pq2 的内容
    std::cout << "pq2: ";
    while (!pq2.empty()) {
        std::cout << pq2.top() << " "; // 访问堆顶元素
        pq2.pop(); // 弹出堆顶元素
    }

    //添加
    std::priority_queue<int> pq;
    // 使用 push 添加元素
    pq.push(10);
    pq.push(30);
    pq.push(20);

    // 访问堆顶元素
    std::cout << "Top element: " << pq.top() << std::endl;

    // 删除堆顶元素
    pq.pop();

    // 获取 priority_queue 的大小
    std::cout << "pq size: " << pq.size() << std::endl;

    // 检查 priority_queue 是否为空
    if (pq.empty()) {
        std::cout << "pq is empty!" << std::endl;
    }

    //使用自定义数据结构
    //std::priority_queue 可以存储自定义数据结构，但需要定义比较函数。

    struct Task {
        int priority;
        std::string name;
    
        // 重载 < 运算符，用于比较优先级
        bool operator<(const Task& other) const {
            return priority < other.priority; // 最大堆
        }
    };

    std::priority_queue<Task> pqCustom;

    // 添加任务
    pqCustom.push({3, "Task 1"});
    pqCustom.push({1, "Task 2"});
    pqCustom.push({2, "Task 3"});

    // 输出任务
    std::cout << "Tasks in priority order:\n";
    while (!pqCustom.empty()) {
        Task task = pqCustom.top();
        std::cout << task.name << " (Priority: " << task.priority << ")\n";
        pqCustom.pop();
    }
    




    return 0;
}