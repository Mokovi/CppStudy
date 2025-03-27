#include "signalton.h"
//饿汉式
Signalton* Signalton::instance = nullptr;
std::mutex Signalton::mtx;

Signalton* Signalton::getInstance(){
    std::lock_guard<std::mutex> lock(mtx);
    if(instance == nullptr)
    {
        instance = new Signalton;
    }
    return instance;
}
Signalton::Signalton(){
    std::cout << "饿汉式单例模式构造函数.\n";
}
Signalton::~Signalton(){
    std::cout << "饿汉式单例模式析构函数.\n";
    if(instance != nullptr)
    {
        delete instance;
        instance = nullptr;
    }
}
void Signalton::show(){
    std::cout << "饿汉式单例模式！\n";
}


//懒汉式
 DatabaseConnect& DatabaseConnect::getInstance(){
    static DatabaseConnect instance;
    return instance;
}
void DatabaseConnect::connectToDatabase(){
    std::cout<<"Connect to Database.\n";
}
DatabaseConnect::DatabaseConnect(){
    std::cout<<"load config.\n";
}
DatabaseConnect::~DatabaseConnect(){
    std::cout<<"懒汉式单例模式析构函数调用.\n";
}
void DatabaseConnect::executeQuery(const std::string& query) {
    std::cout << "Executing [" << query << "] \n";
}