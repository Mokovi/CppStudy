#include <iostream>
#include <set>

/*
multiset
    允许重复元素的有序集合，基于红黑树实现。
    适用场景：需要有序但允许重复的元素集合。
*/

void multiset(){

    // 创建一个 multiset
    std::multiset<int> myMultiset;

    // 插入元素
    myMultiset.insert(10);
    myMultiset.insert(20);
    myMultiset.insert(30);
    myMultiset.insert(20); // 允许重复元素

    // 遍历 multiset
    std::cout << "Multiset elements: ";
    for (const auto& elem : myMultiset) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // 查找元素
    auto it = myMultiset.find(20);
    if (it != myMultiset.end()) {
        std::cout << "Element 20 found in multiset!" << std::endl;
    }

    // 统计某个元素的个数
    std::cout << "Number of 20s in multiset: " << myMultiset.count(20) << std::endl;

    // 删除元素
    myMultiset.erase(20); // 删除所有值为 20 的元素

    // 再次遍历 multiset
    std::cout << "Multiset elements after erasing 20: ";
    for (const auto& elem : myMultiset) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}



/*
set
    有序集合，元素唯一且自动排序，基于红黑树实现。
    适用场景：需要有序且唯一的元素集合。
*/

void set(){
    // 创建一个空的 set
    std::set<int> set1;
    // 使用初始化列表创建 set
    std::set<int> set2 = {3, 1, 4, 1, 5, 9};

    //添加
    std::set<int> set;
    // 使用 insert 添加元素
    set.insert(10);
    set.insert(30);
    set.insert(20);

    // 使用迭代器访问元素
    auto it = set.begin();
    std::advance(it, 1); // 移动到第 2 个元素
    std::cout << "Second element: " << *it << std::endl;

    // 删除指定元素
    set.erase(20);

    // 查找元素
    auto it = set.find(20);
    if (it != set.end()) {
        std::cout << "Element 20 found!" << std::endl;
    } else {
        std::cout << "Element 20 not found!" << std::endl;
    }

    // 获取 set 的大小
    std::cout << "set size: " << set.size() << std::endl;

    // 检查 set 是否为空
    if (set.empty()) {
        std::cout << "set is empty!" << std::endl;
    }

    //默认情况下，std::set 按升序排序。可以通过自定义比较函数实现降序排序。
    // 使用 greater<int> 实现降序排序
    std::set<int, std::greater<int>> set = {10, 20, 30};

    //std::set 可以存储自定义数据结构，但需要定义比较函数。
    struct Person {
        std::string name;
        int age;
    
        // 重载 < 运算符，用于比较
        bool operator<(const Person& other) const {
            return age < other.age; // 按年龄升序排序
        }
    };
    std::set<Person> setPerson;
    // 添加元素
    setPerson.insert({"Alice", 30});
    setPerson.insert({"Bob", 20});
    setPerson.insert({"Charlie", 25});

    // 输出 set 的内容
    std::cout << "People sorted by age:\n";
    for (const auto& person : setPerson) {
        std::cout << person.name << " (" << person.age << ")\n";
    }

    // 合并两个 set
    set1.insert(set2.begin(), set2.end());


    // 查找下界（第一个 >= 25 的元素）
    auto lb = set.lower_bound(25);
    std::cout << "Lower bound of 25: " << *lb << std::endl;
    // 查找上界（第一个 > 30 的元素）
    auto ub = set.upper_bound(30);
    std::cout << "Upper bound of 30: " << *ub << std::endl;


}



int main() {


    multiset();
    set();
    


    return 0;
}