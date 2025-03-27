#ifndef __COMPOSITEPATTERN__H__
#define __COMPOSITEPATTERN__H__

#include <iostream>
#include <vector>
#include <memory>
/*
六、组合模式 (Composite Pattern)
    核心思想：将对象组合成树形结构以表示“部分-整体”的层次结构，使客户端可以统一处理单个对象和组合对象。
    适用场景：文件系统、UI组件树、组织架构管理等具有树形结构的场景。
    核心概念
        组件接口 (Component)：定义所有对象的通用接口（如 display()）。
        叶子节点 (Leaf)：表示树中的单个对象（如文件）。
        组合节点 (Composite)：包含子组件（叶子或其他组合节点）的容器（如目录）。
    
*/
//场景描述：实现一个文件系统，包含文件和目录，目录可以嵌套其他目录或文件。
class FileSysComponent{
public:
    virtual void display(int indent = 0) const = 0;
    virtual ~FileSysComponent() = default;
};
// 叶子节点：文件
class File : public FileSysComponent{
public:
    File(std::string name):name(name){}
    void display(int indent) const override;
private:
    std::string name;
};
// 组合节点：目录
class Directory : public FileSysComponent {
    std::string name;
    std::vector<std::unique_ptr<FileSysComponent>> children;
public:
    Directory(const std::string& name) : name(name) {}
    void add(std::unique_ptr<FileSysComponent> comp) {
        children.push_back(std::move(comp));
    }

    void display(int indent = 0) const override ;
};
#endif