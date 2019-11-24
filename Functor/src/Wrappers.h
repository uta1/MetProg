#pragma once

template<class Function>
class FunctionWrapper {
private:
    Function function;
public:
    FunctionWrapper(const Function& function_) : function(function_) {}

    template<class...Args>
    auto operator()(Args... args) -> decltype(function(args...)) {
        return function(args...);
    }
};

template<class Class, class Method>
class MethodWrapper {
private:
    Class& classInstance;
    Method method;
public:
    MethodWrapper(Class& object, const Method& callable) : classInstance(object), method(callable) {}

    template<class...Args>
    auto operator()(Args... args) -> decltype((classInstance.*method)(args...)) {
        return (classInstance.*method)(args...);
    }
};

