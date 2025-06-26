#include "calculator.h"

float Calculator::add(){
    return num1+num2;
}
float Calculator::minus(){
    return num1-num2;
}
float Calculator::divide(){
    if(num2 < 0.00001 && num2 > -0.00001)
    {
        std::cout << "被除数不能为0." << std::endl;
        return 0;
    }
    return num1/num2;
}
float Calculator::multiply(){
    return num1*num2;
}

