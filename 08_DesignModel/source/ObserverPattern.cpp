#include "ObserverPattern.h"

void ComputerDisplay::update(float temperature){
    std::cout << "[PC] Current temperature: " << temperature << "°C" << std::endl;
}

void PhoneDisplay::update(float temperature){
    std::cout << "[Phone] Current temperature: " << temperature << "°C" << std::endl;
}