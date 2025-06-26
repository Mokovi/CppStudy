#ifndef __COMMANDPATTERN__H__
#define __COMMANDPATTERN__H__
/*
七、命令模式 (Command Pattern)
核心思想：将请求封装为对象，以便参数化客户端、支持请求排队、日志记录或撤销操作。
适用场景：GUI按钮操作、事务管理、任务队列、撤销/重做功能。
核心概念:
    命令接口 (Command)：声明执行操作的接口（如 execute()）。
    具体命令 (Concrete Command)：实现命令接口，绑定接收者（真正执行操作的对象）。
    调用者 (Invoker)：触发命令执行（如按钮点击）。
    接收者 (Receiver)：实际执行业务逻辑的对象。
*/
//场景描述：实现文本编辑器的撤销/重做功能。
#include <iostream>
#include <stack>
#include <string>
#include <memory>
// 接收者：文本编辑器
class TextEditor{
public:
    void addText(const std::string& newText) {
        text += newText;
    }
    void deleteText(int length) {
        if (length > text.size()) length = text.size();
        text.resize(text.size() - length);
    }
    std::string getText() const { return text; }
private:
    std::string text;
};

// 命令接口
class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() = default;
};

// 具体命令：添加文本
class AddTextCommand : public Command {
    TextEditor& editor;
    std::string addedText;
public:
    AddTextCommand(TextEditor& editor, const std::string& text)
        : editor(editor), addedText(text) {}

    void execute() override {
        editor.addText(addedText);
    }

    void undo() override {
        editor.deleteText(addedText.size());
    }
};
// 调用者：命令管理器（支持撤销）
class CommandManager {
    std::stack<std::unique_ptr<Command>> history;
public:
    void executeCommand(std::unique_ptr<Command> cmd);
    void undo();
};









#endif