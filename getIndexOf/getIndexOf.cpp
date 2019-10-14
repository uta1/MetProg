#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::pair;
using std::make_pair;

struct TailElement{
};

struct UnexistingElement{
};

template<class T, class H>
struct Tuple{
    typedef H head;
    typedef T tail;
};

template<class T, class H, class Key> 
struct Counter {
    static const pair<int, bool> getIndexOf() {
	const pair<int, bool> temp = Counter<class H::tail, class H::head, Key>::getIndexOf();
        return make_pair(temp.first + 1, temp.second);
    }
};

template<class Key> 
struct Counter<Key, TailElement, Key> { 
    static const pair<int, bool> getIndexOf() {
        return make_pair(0, true);
    }
};

template<class Key, class H> 
struct Counter<Key, H, Key> { 
    static const pair<int, bool> getIndexOf() {
        return make_pair(0, true);
    }
};

template<class T, class Key> 
struct Counter<T, TailElement, Key> {
    static const pair<int, bool> getIndexOf() {
        return make_pair(-1, false);
    }
};

template<class TupleClass, class key>
int getIndexOf() {
    const pair<int, bool> searchResult = Counter<UnexistingElement, TupleClass, key>::getIndexOf();
    if (searchResult.second) {
        return searchResult.first - 1;
    }
    return -1;
}

int main (int argc, char** argv) {   
    cout << getIndexOf<Tuple<bool, Tuple<int, Tuple<void, TailElement> > >, string>() << endl;
    cout << getIndexOf<Tuple<bool, Tuple<int, Tuple<void, TailElement> > >, bool>() << endl;
    cout << getIndexOf<Tuple<bool, Tuple<int, Tuple<void, TailElement> > >, int>() << endl;
    cout << getIndexOf<Tuple<bool, Tuple<int, Tuple<void, TailElement> > >, void>() << endl;
    cout << getIndexOf<Tuple<bool, Tuple<int, Tuple<void, Tuple<int, Tuple<int, Tuple<void, TailElement> > > > > >, int>() << endl;
    return 0;
}
