#ifndef __CHAINOFRESPONSIBILITY__H__
#define __CHAINOFRESPONSIBILITY__H__
/*
五、责任链模式 (Chain of Responsibility)
功能： 将多个处理对象连接成一条链，请求沿着链传递，直到有一个对象处理它为止,或者沿着链式顺序处理。
核心价值:
    解耦请求的发送者和接收者;
    当需要多个对象按顺序处理同一请求;
    当希望动态指定请求处理流程;
适用场景：审批流程、异常处理链、HTTP请求过滤。
*/
#include <iostream>
#include <memory>
using namespace std;
/*
场景描述：
在企业中，不同金额的报销申请需要不同级别的领导审批（例如：
小于 1000 元 → 直接主管审批
1000~5000 元 → 部门经理审批
大于 5000 元 → 总经理审批
责任链实现：
将各级审批人（主管 → 经理 → 总经理）链接成链，请求（报销单）沿链传递，直到找到能处理它的审批人。
*/
//处理者（Handler）：定义处理请求的接口，通常包含一个指向下一个处理者的引用。
class Handler{
protected:
    std::shared_ptr<Handler> nextHandler;
public:
    virtual void handlerRequest(int amount) = 0;//请求（Request）：需要被处理的对象或数据。这里指amount
    void setNext(std::shared_ptr<Handler> handler){
        nextHandler = handler;
    }
    virtual ~Handler() = default;
};
//具体处理者（Concrete Handler）：实现处理请求的具体逻辑，决定是否处理请求或传递给下一个处理者。
// 具体处理者：经理
class Manager : public Handler {
public:
    void handlerRequest(int amount) override;
};
// 具体处理者：总监
class Director : public Handler {
public:
    void handlerRequest(int amount) override;
};
/*



/*
例子2： Web 请求过滤器链
场景描述：
    一个 HTTP 请求需要经过多个过滤器处理：
        认证检查 → 日志记录 → 数据压缩 → 业务处理
责任链实现：
    每个过滤器作为一个处理者，请求依次通过所有过滤器，每个过滤器可以选择处理或传递。
*/
/*
class HttpRequest;
class Filter {
protected:
    Filter* nextFilter;
public:
    void setNext(Filter* next) { nextFilter = next; }
    virtual void doFilter(HttpRequest& request) = 0;
};
    
class AuthFilter : public Filter {
public:
    void doFilter(HttpRequest& request) override {
        if (!checkAuth(request)) {
            throw "Unauthorized!";
        }
        cout << "Authentication passed." << endl;
        if (nextFilter != nullptr) {
            nextFilter->doFilter(request);
        }
    }
private:
    bool checkAuth(HttpRequest& req) {}//实现认证逻辑
};

class LoggingFilter : public Filter {
public:
    void doFilter(HttpRequest& request) override {
        logRequest(request);
        if (nextFilter != nullptr) {
            nextFilter->doFilter(request);
        }
    }
private:
    void logRequest(HttpRequest& req) {}//记录日志
};
*/
/*
使用示例
AuthFilter auth;
LoggingFilter log;
auth.setNext(&log);
HttpRequest request;
auth.doFilter(request); // 先认证，后记录日志
*/
/*
例子3:游戏中的事件处理
场景描述：
    在游戏中，一个事件（如玩家攻击）可能需要多个系统响应：
    伤害计算 → 音效播放 → 粒子特效 → UI 更新
责任链实现：
    每个系统作为处理者，事件依次触发各系统的处理逻辑。
*/
/*

enum EventType{
    Attack,
    healing
};
class GameEvent{
public:
    EventType type;
};
class GameEventHandler {
protected:
    GameEventHandler* nextHandler;
public:
    void setNext(GameEventHandler* next) { nextHandler = next; }
    virtual void handleEvent(const GameEvent& event) = 0;
};

class DamageSystem : public GameEventHandler {
public:
    void handleEvent(const GameEvent& event) override {
        if (event.type == EventType::Attack) {
            calculateDamage(event);
        }
        if (nextHandler != nullptr) {
            nextHandler->handleEvent(event);
        }
    }
private:
    void calculateDamage(const GameEvent& e) {}//计算伤害
};

class SoundSystem : public GameEventHandler {
public:
    void handleEvent(const GameEvent& event) override {
        if (event.type == EventType::Attack) {
            playSwordSound();
        }
        if (nextHandler != nullptr) {
            nextHandler->handleEvent(event);
        }
    }
private:
    void playSwordSound() {}//播放音效
};
*/



#endif