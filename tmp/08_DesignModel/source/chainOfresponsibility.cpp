#include "chainofresponsibility.h"

void Director::handlerRequest(int amount) {
    if (amount <= 5000) {
        std::cout << "Director approves $" << amount << std::endl;
    } else if (nextHandler) {
        nextHandler->handlerRequest(amount);
    } else {
        std::cout << "No handler available for $" << amount << std::endl;
    }
}

void Manager::handlerRequest(int amount) {
    if (amount <= 1000) {
        std::cout << "Manager approves $" << amount << std::endl;
    } else if (nextHandler) {
        nextHandler->handlerRequest(amount);
    } else {
        std::cout << "No handler available for $" << amount << std::endl;
    }
}