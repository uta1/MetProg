#pragma once

#include "Wrappers.h"
#include "ArgsPack.h"

template<class Delegate, class...Args>
class Functor : ArgsPack<Args...> {
private:
    Delegate delegate;
public:
    typedef ArgsPack<Args...> base;

    Functor(const Delegate& delegate, Args...args) : base(args...), delegate(delegate) {}

    template<class Object>
    auto Call(Object& object) -> decltype(base::Call(MethodWrapper<Object, Delegate>(object, delegate))) const {
        return base::Call(MethodWrapper<Object, Delegate>(object, delegate));
    }

    template<class Callable = Delegate>
    auto Call() -> decltype(base::Call(FunctionWrapper<Callable>(delegate))) const {
        return base::Call(FunctionWrapper<Callable>(delegate));
    }
};

template<class Delegate, class...Args>
Functor<Delegate, Args...> make_functor(const Delegate& delegate, Args...args) {
    return Functor<Delegate, Args...>(delegate, std::forward<Args>(args)...);
}

