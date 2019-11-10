#pragma once

#include "Tuple.h"

template<class TList, template<class> class Processor>
class GenScatterHierarchy;

template<class T1, class T2, template<class> class Processor>
class GenScatterHierarchy<Tuple<T1, T2>, Processor> : public GenScatterHierarchy<T1, Processor>, public GenScatterHierarchy<T2, Processor> {
public:
    typedef Tuple<T1, T2> TList;
    typedef GenScatterHierarchy<T1, Processor> LeftBase;
    typedef GenScatterHierarchy<T2, Processor> RightBase;
};

template<class T, template<class> class Processor>
class GenScatterHierarchy : public Processor<T> {
public:
    typedef Processor<T> LeftBase;
};

template<template<class> class Processor>
class GenScatterHierarchy<TailType, Processor> {
};
