/*
vector
动态数组，支持随机访问，尾部插入和删除高效。
适用场景：需要频繁随机访问且尾部操作较多的情况。
*/
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    /*
        创建
    */
    // 创建一个空的 vector
    std::vector<int> vec1;
    // 创建并初始化一个包含 5 个元素的 vector，初始值为 0
    std::vector<int> vec2(5);
    // 创建并初始化一个包含 5 个元素的 vector，初始值为 10
    std::vector<int> vec3(5, 10);
    // 使用初始化列表创建 vector
    std::vector<int> vec4 = {1, 2, 3, 4, 5};
    // 拷贝构造
    auto vec(vec4);

    /*
        添加
    */
    // 在尾部添加元素
    vec1.push_back(10);
    vec1.push_back(20);
    vec1.push_back(30);
    // 使用 emplace_back 直接构造元素 构造省去了赋值操作,直接在push_back中创建会有一个赋值的过程.
    vec1.emplace_back(40);
    // 输出 vector 内容
    std::cout << "vec1: ";
    for (int i : vec1) {
        std::cout << i << " ";
    }

    /*
        访问
    */
    // 使用下标访问元素
    std::cout << "Element at index 2: " << vec4[2] << std::endl;
    // 使用 at() 访问元素（会检查边界）
    std::cout << "Element at index 3: " << vec4.at(3) << std::endl;
    // 访问第一个和最后一个元素
    std::cout << "First element: " << vec4.front() << std::endl;
    std::cout << "Last element: " << vec4.back() << std::endl;

    /*
        遍历
    */
   std::cout << "Using index: ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
    // 使用范围 for 循环遍历
    std::cout << "Using range-based for loop: ";
    for (int i : vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    // 使用迭代器遍历
    std::cout << "Using iterator: ";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 修改指定位置的元素
    vec[2] = 100;

    // 删除最后一个元素
    vec.pop_back();
    // 删除指定位置的元素（删除第 2 个元素）
    vec.erase(vec.begin() + 1);


    // 获取元素个数
    std::cout << "Size: " << vec.size() << std::endl;
    // 获取当前容量
    std::cout << "Capacity: " << vec.capacity() << std::endl;
    // 调整大小（如果新大小大于当前大小，会用默认值填充）
    vec.resize(10);
    // 预留空间（避免频繁扩容）
    vec.reserve(20);

     // 对 vector 进行升序排序
    std::sort(vec.begin(), vec.end());
    // 输出排序后的 vector
    std::cout << "Sorted vec: ";
    for (int i : vec) {
        std::cout << i << " ";
    }

    // 创建一个 3x3 的二维 vector
    std::vector<std::vector<int>> vec5 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    // 访问二维 vector 的元素
    std::cout << "Element at (1, 2): " << vec5[1][2] << std::endl;
    // 遍历二维 vector
    for (const auto& row : vec5) {
        for (auto val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    std::vector<int> vec6 = {1, 2, 3};
    std::vector<int> vec7 = {4, 5, 6};

    // 交换两个vector的内容
    vec6.swap(vec7);
    // 输出交换后的结果
    std::cout << "vec6: ";
    for (int i : vec6) {
        std::cout << i << " ";
    }
    std::cout << "\nvec7: ";
    for (int i : vec7) {
        std::cout << i << " ";
    }
}