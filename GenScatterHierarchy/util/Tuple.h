#pragma once

struct TailType{
};

template<class T, class H>
struct Tuple{
    typedef H head;
    typedef T tail;
};

