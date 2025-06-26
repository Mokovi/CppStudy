#include <iostream>
#include <cstdlib>


//为整个程序重载全局的 new 和 delete，这种重载会影响所有使用 new 和 delete 的动态内存分配
// 全局重载 operator new
void* operator new(std::size_t size) {
    std::cout << "全局自定义 operator new，大小: " << size << std::endl;
    void* p = std::malloc(size);
    if (!p) throw std::bad_alloc();
    return p;
}

// 全局重载 operator delete
void operator delete(void* p) noexcept {
    std::cout << "全局自定义 operator delete" << std::endl;
    std::free(p);
}

int main() {
    int* p = new int(100); // 将调用全局自定义的 operator new
    std::cout << "值: " << *p << std::endl;
    delete p;              // 调用全局自定义的 operator delete
    return 0;
}
