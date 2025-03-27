#include <iostream>
#include "signalton.h"
#include "factoryPattern.h"
#include <ctime>
#include "strategyPattern.h"
#include "ObserverPattern.h"
#include "chainofresponsibility.h"
#include "compositePattern.h"
#include "commandPattern.h"

int main(){
/*
    Signalton* sg = Signalton::getInstance();
    sg->show();
    DatabaseConnect::getInstance().connectToDatabase();
    DatabaseConnect::getInstance().executeQuery("select * from db;");
*/
/*
    try
    {
        auto logger = LoggerFactory::createLogger(LoggerFactory::FILE);
        // 获取当前时间戳（从1970年1月1日以来的秒数）
        std::time_t now = std::time(nullptr);
        // 将时间转换为字符串形式
        logger->log(std::ctime(&now));
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
    }
*/
/*
    Compressor compressor(std::make_unique<ZipStrategy>());
    compressor.executeCompression("data.txt"); // ZIP压缩
    compressor.setStrategy(std::make_unique<RarStrategy>());
    compressor.executeCompression("data.txt"); // 切换为RAR压缩
*/
/*
    auto station = std::make_shared<WeatherStation>();
    auto phone = std::make_shared<PhoneDisplay>();
    auto pc = std::make_shared<ComputerDisplay>();

    station->addObserver(phone);
    station->addObserver(pc);
    station->setTemperature(25.5); // 触发通知
*/
/*
    // 使用示例：
    auto manager = std::make_shared<Manager>();
    auto director = std::make_shared<Director>();
    manager->setNext(director);

    manager->handlerRequest(800);   // Manager处理
    manager->handlerRequest(2500);  // Director处理
    manager->handlerRequest(10000); // 无处理者
*/
/*
    auto root = std::make_unique<Directory>("Root");
    root->add(std::make_unique<File>("readme.txt"));

    auto src = std::make_unique<Directory>("src");
    src->add(std::make_unique<File>("main.cpp"));
    src->add(std::make_unique<File>("utils.h"));
    root->add(std::move(src));
    root->display();
*/
    TextEditor editor;
    CommandManager manager;

    manager.executeCommand(std::make_unique<AddTextCommand>(editor, "Hello"));
    std::cout << editor.getText() << std::endl; // 输出: Hello
    manager.executeCommand(std::make_unique<AddTextCommand>(editor, " World!"));
    std::cout << editor.getText() << std::endl; // 输出: Hello World!
    manager.undo();
    std::cout << editor.getText() << std::endl; // 输出: Hello

    return 0;
}