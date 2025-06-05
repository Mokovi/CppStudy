#include <iostream>
/*
一、核心概念    
    异常（Exception）：在程序运行中发生的错误或意外情况，例如数组越界、除零、文件打开失败等。
    抛出异常（throw）：当程序检测到错误时，可以使用 throw 抛出一个异常对象。
    捕获异常（catch）：通过 try...catch 语句块捕获抛出的异常，并在 catch 块中处理该异常。
    异常传播与栈展开：当异常抛出后，程序会沿着调用栈向上寻找匹配的 catch 块，在此过程中会依次调用局部对象的析构函数，释放相关资源。

二、基本语法
    1. 抛出基本类型异常
        try 块：将可能出现异常的代码放在 try 块中。
        throw 语句：当检测到错误时，使用 throw 抛出一个异常对象（通常继承自 std::exception）。
        catch 块：用于捕获特定类型的异常，建议捕获异常的引用，避免不必要的拷贝，同时支持多态。
                double divide(int a, int b) {
                    if (b == 0) {
                        throw "Division by zero!"; // 抛出const char*异常
                    }
                    return static_cast<double>(a) / b;
                }
                try {
                    cout << divide(10, 0) << endl;
                } catch (const char* msg) {
                    cerr << "Error: " << msg << endl; // 捕获并处理异常
                }
    2. 抛出标准异常
                try {
                    throw invalid_argument("Division by zero!");
                } catch (cont invalid_argument& e) {
                    std::cerr << e.what() << std::endl;
                }

    3. catch(...) 捕获所有异常
                try {
                    // ...
                } catch (...) {
                    // 处理所有异常
                    std::cerr << "捕获到未知异常" << std::endl;
                }
三、异常类  
    1. 标准异常类
        C++ 标准库定义了一系列异常类，所有这些异常类都继承自 std::exception。例如：
            std::runtime_error：运行时错误
            std::logic_error：逻辑错误
            std::bad_alloc：内存分配失败
        通过调用异常对象的 what() 成员函数，可以获得错误描述信息.
    2. 自定义异常类
        继承自std::exception，提供更清晰的错误信息
                class DivisionByZeroException : public std::exception {
                private:
                    std::string message;
                public:
                    DivisionByZeroException(const std::string& msg) : message(msg) {}
                    const char* what() const noexcept override {
                        return message.c_str();
                    }
                };
四、异常传播与栈展开
    当异常被抛出后，如果当前函数内没有相应的 catch 块捕获，异常将沿调用栈向上传播；在这一过程中，局部对象的析构函数会被自动调用，这一过程称为栈展开（stack unwinding）。
这种机制确保了即使发生异常，局部资源（如动态分配的内存、文件句柄等）也能通过 RAII 自动释放，从而避免资源泄露。

五、异常安全
    基本保证：程序保持有效状态（无资源泄漏，数据一致）。
    强烈保证：操作要么完全成功，要么完全回滚（事务语义）。
                class Database {
                public:
                    void updateRecord(int id, const std::string& data) {
                        auto backup = currentData_; // 备份当前状态
                        currentData_ = data;        // 尝试修改
                        if (!validateData()) {
                            currentData_ = backup;  // 验证失败，回滚
                            throw std::runtime_error("Invalid data");
                        }
                    }
                private:
                    std::string currentData_;
                };
    不抛保证：函数承诺不抛出异常（标记为noexcept）。
                void safeFunction() noexcept {
                    // 保证不抛出异常
                }

六、总结
    1. 捕获异常时最好用 const 引用：例如 catch(const std::exception& e)，这样避免了不必要的拷贝、以及误修改。
    2. 尽量避免捕获具体类型：如果可以，使用标准异常类的基类，以利用多态特性。（如 std::runtime_error、std::logic_error 等）
    3. 不要在异常处理代码中再次抛出异常（除非使用 throw  重新抛出原异常），以避免异常嵌套复杂化问题。
    4. 在 catch 块中，可以使用 throw; 重抛当前捕获的异常，以便在更高层进行处理或记录日志
    5. 保证析构函数不抛异常，若析构函数在栈展开时被调用，且抛出异常，程序会终止。
    6. 利用RAII确保资源安全。
    7. 谨慎使用异常：异常处理适合处理严重错误，而非普通控制流，其资源消耗大!!
    8. 在多线程环境下，注意异常信息在各线程间的传递和处理
        由于线程间的异常不会自动传播到其他线程，需要在每个线程中捕获异常，并借助 std::promise/std::future 等机制将异常信息传递给主线程处理。
*/
#include <exception>

class DivisionByZeroException : public std::exception{
private:
    std::string msg;
public:
    DivisionByZeroException(const std::string& str):msg(str) {}
    const char* what() const noexcept override{
        return msg.c_str();
    }
};

double division(int a, int b){

    if (b == 0){
        throw DivisionByZeroException("除数为0!");
    }
    return static_cast<double>(a) / b;
}


int main(){
    try{
        division(3,0);
    }
    catch(const DivisionByZeroException& e){
        std::cerr << "custom error: " << e.what() << std::endl;
        //throw;
    }
    catch(const std::exception& e){
        std::cerr << "standard error: " << e.what() << std::endl;
    }
    catch(...){
        std::cerr << "unexcepted error. " << std::endl;
    }

    return 0;
}