// std: c++17
#include <utility>
#include <vector>

template <class T>
void take(T&& t) { std::vector<int> v(std::forward<T>(t)); (void)v; }

int main() {
    take(std::vector<int>{1, 2, 3});               // name the type, or give the parameter a default: template <class T = std::vector<int>>
}
