#include <cstring>
#include <iostream>
#include "util/TupleGetter.h"

using std::cout;
using std::endl;
using std::string;

template<class T>
struct IdentityProcessor : BaseProcessor<T> {
    T process() {
        return arg;
    }
    static T arg;
};
template<class T> T IdentityProcessor<T>::arg;

int main() {
    IdentityProcessor<string>::arg = "UTA";
    IdentityProcessor<int>::arg = 1998;
    IdentityProcessor<char>::arg = '[';

    cout << TupleGetter<string, Tuple<string, Tuple<int, Tuple<char, TailType> > >, IdentityProcessor>::get() << endl;
    cout << TupleGetter<int, Tuple<string, Tuple<int, Tuple<char, TailType> > >, IdentityProcessor>::get() << endl;
    cout << TupleGetter<char, Tuple<string, Tuple<int, Tuple<char, TailType> > >, IdentityProcessor>::get() << endl;

    return 0;
} 
