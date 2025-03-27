/*
list
    双向链表，插入和删除高效，但不支持随机访问。
    适用场景：频繁在任意位置插入或删除元素。
*/
#include <iostream>
#include <list>


int main()
{
    //创建
    // 创建一个空的 list
    std::list<int> list1;
    // 创建并初始化一个包含 5 个元素的 list，初始值为 0
    std::list<int> list2(5);
    // 创建并初始化一个包含 5 个元素的 list，初始值为 10
    std::list<int> list3(5, 10);
    // 使用初始化列表创建 list
    std::list<int> list4 = {1, 2, 3, 4, 5};

    //添加
    std::list<int> list;
    // 在尾部添加元素
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    // 在头部添加元素
    list.push_front(5);
    list.push_front(1);
    // 使用 emplace_back 和 emplace_front 直接构造元素
    list.emplace_back(40);
    list.emplace_front(0);

    //访问
    // 访问第一个和最后一个元素
    std::cout << "First element: " << list.front() << std::endl;
    std::cout << "Last element: " << list.back() << std::endl;


    //遍历
    // 使用范围 for 循环遍历
    std::cout << "Using range-based for loop: ";
    for (int i : list) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    // 使用迭代器遍历
    std::cout << "Using iterator: ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }

    // 获取元素个数
    std::cout << "Size: " << list.size() << std::endl;

     // 对 list 进行升序排序
     list.sort();

    // 去重（需要先排序）
    list.sort();
    list.unique();

     // 合并两个 list（需要先排序）
     list1.sort();
     list2.sort();
     list1.merge(list2);

    // 交换两个 list 的内容
    list1.swap(list2);

    // 反转 list
    list.reverse();

    // 在指定位置插入元素
    auto it = list.begin();
    std::advance(it, 2); // 将迭代器移动到第 3 个位置
    list.insert(it, 100);

    


    return 0;
}