#pragma once

#include "Tuple.h"
#include "GenScatterHierarchy.h"

template<class T, class TList, template<class> class Processor>
class TupleGetter;

template<class T>
struct BaseProcessor{
    virtual T process();
};

template<class T, class T1, class T2, template<class> class BaseProcessor>
class TupleGetter<T, Tuple<T1, T2>, BaseProcessor> {
public:
    static T get() {
        return TupleGetter<T, T2, BaseProcessor>::get();
    }
};

template<class T, class T2, template<class> class BaseProcessor>
class TupleGetter<T, Tuple<T, T2>, BaseProcessor> {
public:
    static T get() {
        typename GenScatterHierarchy<Tuple<T, T2>, BaseProcessor>::LeftBase temprorary;
        return temprorary.process();
    }
};

