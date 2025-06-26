#include <iostream>
#include <stack>
#include <vector>
/*
stack
    后进先出（LIFO）容器，基于deque或list实现。
    适用场景：需要后进先出逻辑，如函数调用栈。
*/

int main(){

    //创建
    // 创建一个空的 stack
    std::stack<int> stack1;
    // 使用 deque 初始化 stack
    std::deque<int> deque = {1, 2, 3, 4, 5};
    std::stack<int> stack2(deque);


    //添加
    std::stack<int> stack;
    // 使用 push 添加元素
    stack.push(10);
    stack.push(20);
    stack.push(30);

    // 访问栈顶元素
    std::cout << "Top element: " << stack.top() << std::endl;
    
    // 删除栈顶元素
    stack.pop();

    // 获取 stack 的大小
    std::cout << "Stack size: " << stack.size() << std::endl;

    // 检查 stack 是否为空
    if (stack.empty()) {
    std::cout << "Stack is empty!" << std::endl;
    }

    // 交换两个 stack 的内容
    stack1.swap(stack2);

    //std::stack 默认使用 std::deque 作为底层容器，但也可以指定其他容器（如 std::vector 或 std::list）。
    // 使用 vector 作为底层容器
    std::stack<int, std::vector<int>> stack;

    // 输出 stack2 的内容
    std::cout << "Stack2: ";
    while (!stack2.empty()) {
        std::cout << stack2.top() << " "; // 访问栈顶元素
        stack2.pop(); // 弹出栈顶元素
    }
    
    return 0;
}

