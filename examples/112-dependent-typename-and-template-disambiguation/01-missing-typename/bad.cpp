// expect: compile-error
// std: c++17
// A qualified name that depends on T is assumed to be a value unless prefixed with typename.
#include <vector>

template <class C>
void f(const C& c) {
    C::value_type first = c.front();               // error: needs typename
    (void)first;
}

int main() { f(std::vector<int>{1}); }
