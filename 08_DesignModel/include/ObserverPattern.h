#ifndef __OBSERVERPATTERN__H__
#define __OBSERVERPATTERN__H__

/*
四、观察者模式 (Observer Pattern)
功能：定义对象间的一对多依赖关系，当一个对象状态改变时，所有依赖它的对象自动收到通知。
适用场景：事件处理系统、股票价格变动通知等。
*/
#include <iostream>
#include <vector>
#include <memory>

// 观察者接口
class Observer{
public:
    virtual void update(float temperature) = 0;
    virtual ~Observer() = default;
};
// 主题接口
class Subject{
public:
    virtual void addObserver(std::shared_ptr<Observer> o) = 0;
    virtual void notifyObserver() = 0;
};
// 具体主题：气象站
class WeatherStation : public Subject{
public:
    void addObserver(std::shared_ptr<Observer> o) override{
        observers.push_back(o);
    }
    void setTemperature(float temperature){
        this->temperature = temperature;
        notifyObserver();
    }
    void notifyObserver() override{
        for(auto& o : observers)
        {
            o->update(temperature);
        }
    }
private:
    std::vector<std::shared_ptr<Observer>> observers;
    float temperature;
};
// 具体观察者：手机显示
class PhoneDisplay : public Observer{
public:
    void update(float temperature) override;
};
// 具体观察者：电脑显示
class ComputerDisplay : public Observer{
public:
    void update(float temperature) override ;
};



#endif
