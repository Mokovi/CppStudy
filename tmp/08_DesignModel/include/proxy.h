#ifndef __PROXY__H__
#define __PROXY__H__
/*
八、代理模式 (Proxy Pattern)
    核心思想：为其他对象提供一种代理以控制对这个对象的访问。
    适用场景：延迟加载、访问控制、日志记录、远程对象调用等。
    核心概念：
        抽象主题 (Subject)：定义真实对象和代理的公共接口。
        真实主题 (Real Subject)：实际执行业务逻辑的对象。
        代理 (Proxy)：控制对真实主题的访问，并可能负责创建或管理它。
*/
#include <iostream>
#include <string>
#include <memory>
#include <thread>
#include <unordered_map>
//延迟加载：实现一个图片加载代理，在真正需要显示图片时才加载大文件。
//抽象主题
class Image{
public:
    virtual void display() = 0;
    virtual ~Image() = default;
};
// 真实主题：高分辨率图片（加载耗时）
class HighResImage : public Image {
    std::string filename;
public:
    HighResImage(const std::string& filename) : filename(filename) {
        loadFromDisk(); // 模拟耗时操作
    }

    void display() override {
        std::cout << "Displaying " << filename << std::endl;
    }

private:
    void loadFromDisk() {
        std::cout << "Loading " << filename << "..." << std::endl;
    }
};
// 代理：延迟加载图片
class ImageProxy : public Image {
    std::string filename;
    HighResImage* realImage = nullptr; // 延迟初始化
public:
    ImageProxy(const std::string& filename) : filename(filename) {}

    void display() override {
        if (realImage == nullptr) {
            realImage = new HighResImage(filename); // 按需加载
        }
        realImage->display();
    }

    ~ImageProxy() {
        delete realImage;
    }
};

void testProxy(){
    ImageProxy imageProxy("photo.jpg");
    // 图片尚未加载
    imageProxy.display(); // 第一次调用时加载并显示
}


//保护代理:根据权限控制对敏感对象的访问。
// 接口：敏感文档
class Document {
public:
    virtual void view() = 0;
    virtual ~Document() = default;
};

// 真实对象：机密文档
class ConfidentialDocument : public Document {
public:
    void view() override {
        std::cout << "Displaying confidential content." << std::endl;
    }
};
    
// 代理：验证访问权限
class DocumentProxy : public Document {
    Document* realDoc;
    std::string userRole;
public:
    DocumentProxy(const std::string& role) : userRole(role) {}
    void view() override {
        if (userRole == "admin") {
            if (!realDoc) realDoc = new ConfidentialDocument();
            realDoc->view();
        } else {
            std::cout << "Access denied!" << std::endl;
        }
    }
    ~DocumentProxy() { delete realDoc; }
};
void testDocument()
{
    // 使用示例：
    DocumentProxy userProxy("user");
    userProxy.view(); // 输出: Access denied!

    DocumentProxy adminProxy("admin");
    adminProxy.view(); // 输出: Displaying confidential content.
}

//缓存代理（性能优化）缓存昂贵操作的结果，避免重复计算或请求。
// 接口：数据获取服务
class DataService {
public:
    virtual std::string fetchData(int id) = 0;
    virtual ~DataService() = default;
};
// 真实对象：耗时操作（如数据库查询）
class ExpensiveDataService : public DataService {
public:
    std::string fetchData(int id) override {
        // 模拟耗时操作
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return "Data for ID " + std::to_string(id);
    }
};
// 代理：添加缓存层
class CachingProxy : public DataService {
    DataService* service;
    std::unordered_map<int, std::string> cache;
public:
    CachingProxy() : service(new ExpensiveDataService()) {}
    std::string fetchData(int id) override {
        if (cache.find(id) == cache.end()) {
            cache[id] = service->fetchData(id); // 首次查询缓存
        }
        return cache[id];
    }
    ~CachingProxy() { delete service; }
};
void testCache()
{
    // 使用示例：
    CachingProxy proxy;
    auto data1 = proxy.fetchData(1); // 耗时 2s
    auto data2 = proxy.fetchData(1); // 立即返回缓存结果
}

#endif