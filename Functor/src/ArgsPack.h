#pragma once

template<class...T>
class ArgsPack;

template<>
class ArgsPack<> {
public:
    ArgsPack() {};

    template<class Delegate, class...Args>
    auto Call(Delegate delegate, Args... args) -> decltype(delegate(args...)) {
        return delegate(args...);
    }
};

template<typename T>
T* ConvertToPtr(T& t) {
    return &t;
}

template<typename T>
T* ConvertToPtr(T* t) {
    return t;
}

template<typename T>
T& ConvertToRef(T& t) {
    return t;
}

template<typename T>
T& ConvertToRef(T* t) {
    return *t;
}

template<class Head, class...Tail>
class ArgsPack<Head, Tail...> : ArgsPack<Tail...> {
private:
    Head headArg;
public:
    typedef ArgsPack<Tail...> base;

    ArgsPack(Head head, Tail... args) : base(args...), headArg(head) {}

    template<class Delegate, class...Args>
    auto Call(const Delegate& delegate, Args... args) ->
    decltype(base::Call(delegate, args..., ConvertToRef(headArg))) {
        return base::Call(delegate, args..., ConvertToRef(headArg));
    }

    template<class Delegate, class...Args>
    auto Call(const Delegate& delegate, Args... args) ->
    decltype(base::Call(delegate, args..., ConvertToPtr(headArg))) {
        return base::Call(delegate, args..., ConvertToPtr(headArg));
    }
};

