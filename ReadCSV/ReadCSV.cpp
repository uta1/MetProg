#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::tuple;
using std::string;
using std::locale;

struct CommaDelimiter : std::ctype<char> {
    CommaDelimiter() : std::ctype<char>(get_table()) {}
    static mask const* get_table() {
        static mask rc[table_size];
        rc[','] = std::ctype_base::space;
        rc['\n'] = std::ctype_base::space;
        return &rc[0];
    }
};

template <int N>
class Scanner{
public:
    template<class T, class... ExtraTypes>
    static void Scan(std::istream& is, tuple<T, ExtraTypes...>* arg) {
        is >> std::get<std::tuple_size<tuple<T, ExtraTypes...>>::value - 1 - N>(*arg);
        Scanner<N - 1>::Scan(is, arg);
    }
};

template <>
class Scanner<0> {
public:
    template<class T, class... ExtraTypes>
    static void Scan(std::istream& is, tuple<T, ExtraTypes...>* arg) {
        is >> std::get<std::tuple_size<tuple<T, ExtraTypes...>>::value - 1>(*arg);
    }
};

template <int N>
class Writer {
public:
    template<class T, class... ExtraTypes>
    static void Write(const tuple<T, ExtraTypes...>* arg) {
        cout << std::get<std::tuple_size<tuple<T, ExtraTypes...>>::value - 1 -N>(*arg) << endl;;
        Writer<N - 1>::Write(arg);
    }
};

template <>
class Writer<0> {
public:
    template<class T, class... ExtraTypes>
    static void Write(const tuple<T, ExtraTypes...>* arg) {
        cout << std::get<std::tuple_size<tuple<T, ExtraTypes...>>::value - 1>(*arg) << endl << endl;
    }
};

template<class T, class... ExtraTypes>
vector<tuple<T, ExtraTypes...>> readScv(const char* filepath) {
    vector<tuple<T, ExtraTypes...>> v;
    
    std::filebuf fb;
    if (fb.open(filepath, std::ios::in)) {
        std::istream is(&fb);
        is.imbue(locale(is.getloc(), new CommaDelimiter));
        
        tuple<T, ExtraTypes...> current;
        while (is) {
            Scanner<std::tuple_size<tuple<T, ExtraTypes...>>::value - 1>::Scan(is, &current);
            if (is) {
                v.push_back(current);
            }
        }
        
        fb.close();
    }
    
    return std::move(v);
}

template<class T, class... ExtraTypes>
void printVectorOfTuples(const vector<tuple<T, ExtraTypes...>>* v) {
    for (int i = 0; i < v->size(); ++i) {
        Writer<std::tuple_size<tuple<T, ExtraTypes...>>::value - 1>::Write(&v->at(i));
    }
}

int main (int argc, char** argv) {    
    auto v = readScv<int, string, double, char>(argv[1]);
    printVectorOfTuples<int, string, double, char>(&v);
    return 0;
}
