#include <iostream>

class Calculator{
public:
    Calculator(float num1, float num2):num1(num1),num2(num2){}
    ~Calculator(){}
    float add();
    float minus();
    float divide();
    float multiply();
    void setNum1(float num1) {this->num1 = num1;}
    void setNum2(float num2) {this->num2 = num2;}
private:
    float num1;
    float num2;
};

