// expect: compile-error
// std: c++17
// A braced-init-list has no type, so T&& cannot be deduced from it.
#include <vector>

template <class T>
void take(T&& t) { std::vector<int> v(std::forward<T>(t)); (void)v; }

int main() {
    take({1, 2, 3});                               // error: couldn't deduce template parameter 'T'
}
