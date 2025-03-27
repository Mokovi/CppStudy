/*
map
    有序键值对容器，键唯一且自动排序，基于红黑树实现。
    适用场景：需要键值对且键唯一的有序集合。
*/


#include <iostream>
#include <map> // map 头文件

int main() {
    // 创建一个 map
    std::map<std::string, int> myMap;

    // 插入键值对
    myMap["Alice"]   = 25;
    myMap["Bob"]     = 30;
    myMap["Charlie"] = 35;
    myMap.insert({"David", 40}); // 另一种插入方式

    // 遍历 map
    std::cout << "Map elements: " << std::endl;
    for (const auto& pair : myMap) {
        std::cout << "  " << pair.first << ": " << pair.second << std::endl;
    }

    // 查找元素
    auto it = myMap.find("Bob");
    if (it != myMap.end()) {
        std::cout << "\nFound Bob, age: " << it->second << std::endl;
    } else {
        std::cout << "\nBob not found!" << std::endl;
    }

    // 修改元素
    myMap["Alice"] = 26; // 修改 Alice 的年龄
    std::cout << "\nAlice's new age: " << myMap["Alice"] << std::endl;

    // 删除元素
    myMap.erase("Charlie"); // 删除键为 "Charlie" 的键值对

    // 再次遍历 map
    std::cout << "\nMap elements after erasing Charlie: " << std::endl;
    for (const auto& pair : myMap) {
        std::cout << "  " << pair.first << ": " << pair.second << std::endl;
    }

    // 检查键是否存在
    if (myMap.count("David") > 0) {
        std::cout << "\nDavid exists in the map!" << std::endl;
    } else {
        std::cout << "\nDavid does not exist in the map!" << std::endl;
    }

    return 0;
}