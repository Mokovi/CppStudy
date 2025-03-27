#ifndef __STRATEGYPATTERN__H__
#define __STRATEGYPATTERN__H__

#include <iostream>
#include <memory>
/*
三、策略模式 (Strategy Pattern)
功能：定义算法族，使它们可互换，让算法独立于使用它的客户端。
适用场景：支付方式选择、排序算法切换等需要动态改变行为的场景。
*/

//压缩算法选择
// 策略接口
class CompressionStrategy{
public:
    virtual void compress(const std::string& file) = 0;
    virtual ~CompressionStrategy() = default;
};
// 具体策略：ZIP压缩
class ZipStrategy : public CompressionStrategy{
public:
    void compress(const std::string& file) override {
        std::cout << "Compressing " << file << " using ZIP" << std::endl;
    }
};

// 具体策略：RAR压缩
class RarStrategy : public CompressionStrategy{
public:
    void compress(const std::string& file) override {
        std::cout << "Compressing " << file << " using RAR" << std::endl;
    }
};
// 上下文类
class Compressor{
private:
    std::unique_ptr<CompressionStrategy> strategy;

public:
    explicit Compressor(std::unique_ptr<CompressionStrategy> strategy):strategy(std::move(strategy)){}
    /*
        explicit 关键字用于标记构造函数,其主要作用是禁止隐式转换，确保对象只能通过显式调用构造函数来创建。
        默认情况下，一个只带一个参数的构造函数可以用作隐式转换:
            class MyClass {
            public:
                MyClass(int x) : value(x) {}  // 普通构造函数
            private:
                int value;
            };

            void func(MyClass obj) {
                // ...
            }

            int main() {
                func(10); // 隐式将 10 转换为 MyClass 对象
                return 0;
            }
        上面的代码中，传递给 func 的整数 10 会隐式转换为 MyClass 对象。如果不希望这种隐式转换发生，可以使用 explicit 关键字：
            class MyClass {
            public:
                explicit MyClass(int x) : value(x) {}  // 显式构造函数
            private:
                int value;
            };

            void func(MyClass obj) {
                // ...
            }

            int main() {
                // func(10); // 编译错误：不能从 int 隐式转换为 MyClass
                func(MyClass(10)); // 必须显式转换
                return 0;
            }
    */
   void setStrategy(std::unique_ptr<CompressionStrategy> newStrategy);

    void executeCompression(const std::string& file);

};









#endif