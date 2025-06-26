/*
deque
    双端队列，支持头部和尾部的高效插入与删除，允许随机访问。
    适用场景：需要在两端频繁操作且偶尔随机访问。
*/
#include <iostream>
#include <deque>
#include <algorithm>

int main() {
    //创建
    // 创建一个空的 deque
    std::deque<int> deque1;
    // 创建并初始化一个包含 5 个元素的 deque，初始值为 0
    std::deque<int> deque2(5);
    // 创建并初始化一个包含 5 个元素的 deque，初始值为 10
    std::deque<int> deque3(5, 10);
    // 使用初始化列表创建 deque
    std::deque<int> deque4 = {1, 2, 3, 4, 5};

    //添加
    std::deque<int> deque;
    // 在尾部添加元素
    deque.push_back(10);
    deque.push_back(20);
    deque.push_back(30);
    // 在头部添加元素
    deque.push_front(5);
    deque.push_front(1);
    // 使用 emplace_back 和 emplace_front 直接构造元素
    deque.emplace_back(40);
    deque.emplace_front(0);

    //访问
    // 使用下标访问元素
    std::cout << "Element at index 2: " << deque[2] << std::endl;
    // 使用 at() 访问元素（会检查边界）
    std::cout << "Element at index 3: " << deque.at(3) << std::endl;
    // 访问第一个和最后一个元素
    std::cout << "First element: " << deque.front() << std::endl;
    std::cout << "Last element: " << deque.back() << std::endl;

    //遍历
    // 使用下标遍历
    std::cout << "Using index: ";
    for (size_t i = 0; i < deque.size(); ++i) {
        std::cout << deque[i] << " ";
    }
    std::cout << std::endl;
    // 使用范围 for 循环遍历
    std::cout << "Using range-based for loop: ";
    for (int i : deque) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    // 使用迭代器遍历
    std::cout << "Using iterator: ";
    for (auto it = deque.begin(); it != deque.end(); ++it) {
        std::cout << *it << " ";
    }

    //删除
    // 删除头部元素
    deque.pop_front();
    // 删除尾部元素
    deque.pop_back();
    // 删除指定位置的元素（删除第 2 个元素）
    auto it = deque.begin();
    std::advance(it, 1);
    deque.erase(it);

    // 获取元素个数
    std::cout << "Size: " << deque.size() << std::endl;

    // 对 deque 进行升序排序
    std::sort(deque.begin(), deque.end());

    // 交换两个 deque 的内容
    deque1.swap(deque2);

    // 反转 deque
    std::reverse(deque.begin(), deque.end());

    // 在指定位置插入元素
    auto it = deque.begin();
    std::advance(it, 2); // 将迭代器移动到第 3 个位置
    deque.insert(it, 100);




    return 0;
}