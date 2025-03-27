#ifndef __SIGNALTON__H__
#define __SIGNALTON__H__

#include <iostream>
#include <mutex>
/*
一、单例模式 (Singleton Pattern)
    1.功能：确保一个类仅有一个实例，并提供全局访问点。
    2.适用场景：配置管理、日志系统、线程池等需要唯一实例的场景。
    3.实现要点：
        私有化构造函数和拷贝控制成员（禁用拷贝和赋值）。
        通过静态方法获取实例（C++11 后利用局部静态变量实现线程安全）。
*/
//饿汉式 需要用到时才创建实例 线程不安全 需要加锁才能达到线程安全
class Signalton{
public:
    static Signalton* getInstance();
    //禁止拷贝构造函数与赋值运算符重载
    Signalton(const Signalton&) = delete;
    Signalton& operator=(const Signalton&) = delete;
    void show();
    
private:
    Signalton();
    ~Signalton();
    static Signalton* instance;
    static std::mutex mtx;
};

//懒汉式 运行时便创建了实例 线程安全
//应用场景：数据库连接
class DatabaseConnect{
public:
    DatabaseConnect(const DatabaseConnect&) = delete;
    DatabaseConnect& operator=(const DatabaseConnect&) = delete;
    static DatabaseConnect& getInstance();
    void connectToDatabase();
    void executeQuery(const std::string& query);
private:
    DatabaseConnect();
    ~DatabaseConnect();
};

#endif