// std: c++17
#include <vector>

template <class C>
void f(const C& c) {
    typename C::value_type first = c.front();
    (void)first;
}

int main() { f(std::vector<int>{1}); }
