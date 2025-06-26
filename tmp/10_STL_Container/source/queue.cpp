/*
queue
    先进先出（FIFO）容器，基于deque或list实现。
    适用场景：需要先进先出逻辑，如任务调度。
*/

#include <iostream>
#include <queue>
#include <list>


//std::queue 常用于实现广度优先搜索（BFS）算法。
void BFS(const std::vector<std::vector<int>>& graph, int start) {
    std::vector<bool> visited(graph.size(), false);
    std::queue<int> queue;

    queue.push(start);
    visited[start] = true;

    while (!queue.empty()) {
        int node = queue.front();
        queue.pop();
        std::cout << node << " ";

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                queue.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }
}

void testBfs(){
    // 图的邻接表表示
    std::vector<std::vector<int>> graph = {
        {1, 2},    // 节点 0 的邻居
        {0, 3, 4}, // 节点 1 的邻居
        {0, 5},    // 节点 2 的邻居
        {1},       // 节点 3 的邻居
        {1},       // 节点 4 的邻居
        {2}        // 节点 5 的邻居
    };

    // 从节点 0 开始 BFS
    std::cout << "BFS traversal: ";
    BFS(graph, 0);
}


int main() {

    // 创建一个空的 queue
    std::queue<int> queue1;
    // 使用 deque 初始化 queue
    std::deque<int> deque = {1, 2, 3, 4, 5};
    std::queue<int> queue2(deque);

    //添加
    std::queue<int> queue;
    // 使用 push 添加元素
    queue.push(10);
    queue.push(20);
    queue.push(30);

    // 访问队头元素
    std::cout << "Front element: " << queue.front() << std::endl;

    // 删除队头元素
    queue.pop();

    // 获取 queue 的大小
    std::cout << "queue size: " << queue.size() << std::endl;

    // 检查 queue 是否为空
    if (queue.empty()) {
        std::cout << "queue is empty!" << std::endl;
    }

    // 交换两个 queue 的内容
    queue1.swap(queue2);

    //std::queue 默认使用 std::deque 作为底层容器，但也可以指定其他容器（如 std::list）。
    // 使用 list 作为底层容器
    std::queue<int, std::list<int>> queue;


    // 输出 queue2 的内容
    std::cout << "queue2: ";
    while (!queue2.empty()) {
        std::cout << queue2.front() << " "; // 访问队头元素
        queue2.pop(); // 弹出队头元素
    }

    testBfs();

    return 0;
}