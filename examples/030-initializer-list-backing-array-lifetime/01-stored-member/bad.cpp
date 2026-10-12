// std: c++17
// sanitize: address
// An initializer_list is a view of a temporary array; copying the list does not extend the array.
#include <cstdio>
#include <initializer_list>

struct Samples {
    std::initializer_list<int> values;
    Samples(std::initializer_list<int> v) : values(v) {}   // stores the view only
};

int main(int argc, char**) {
    Samples s{argc, argc + 1, argc + 2};                    // the backing array dies at the end of this statement
    std::printf("%d\n", *s.values.begin());                 // UB: use after scope
}
