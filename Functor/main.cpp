#include <iostream>
#include <string>

#include "src/Functor.h"

using std::cout;
using std::endl;
using std::string;

char func(int a, char b, string s) {
    cout << "func: " << endl;
    cout << a << " " << b << " " << s << endl;
    
    return 'x';
}

const auto lambdaFunc = [](int a, char b, string s) {
    cout << "lambda: " << endl;
    cout << a << " " << b << " " << s << endl;
    cout << endl;
};

class ExampleClass {
public:
    int val;

    int print(int a, char b, string s) {
        cout << "class: " << endl;
        cout << a << " " << b << " " << s << " " << val << endl;
        
        return 1000;
    }
};

int main() {
    auto functorFunc = make_functor(&func, 123, 'p', string("string"));
    auto funcRes = functorFunc.Call();
    cout << "funcRes: " << funcRes << endl;
    cout << endl;

    auto functorLambda = make_functor(lambdaFunc, 123, 'p', "string");
    functorLambda.Call();
    
    ExampleClass exampleClass;
    exampleClass.val = 999;
    auto functorClass = make_functor(&ExampleClass::print, 123, 'p', string("string"));
    auto methodRes = functorClass.Call(exampleClass);
    cout << "methodRes: " << methodRes << endl;
    
    return 0;
}

