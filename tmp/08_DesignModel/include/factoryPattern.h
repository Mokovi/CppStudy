#ifndef __FACTORYPATTERN__H__
#define __FACTORYPATTERN__H__

#include <iostream>
#include <memory>
/*
二、工厂模式 (Factory Pattern)
功能：将对象创建逻辑封装到工厂类，实现创建与使用的解耦。
适用场景：需要根据不同条件动态创建对象（如日志记录器、数据库驱动）。
*/
//实例 日志记录器:

// 抽象产品接口
class Logger{
public:
    virtual void log(const std::string& message) = 0;
    virtual ~Logger() = default;//多态一定要注意虚析构函数，不然子类无法析构
};
// 具体产品类：文件日志
class FileLogger : public Logger{
public:
    void log(const std::string& message) override{
        std::cout << "Writting to file : " << message <<std::endl;
    }
};
// 具体产品类：控制台日志
class ConsoleLogger : public Logger{
public:
    void log(const std::string& message) override{
        std::cout << "Console output : " << message <<std::endl;
    }
};
// 工厂类
class LoggerFactory{
public:
    enum LoggerType{
        FILE,
        CONSOLE
    };
    static std::unique_ptr<Logger> createLogger(LoggerType type);
};

#endif