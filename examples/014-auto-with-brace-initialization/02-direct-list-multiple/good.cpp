// std: c++17
// Make the element type uniform, or state the container type.
#include <cstdio>
#include <initializer_list>
#include <vector>

int main() {
    auto y = {1.0, 2.5};                     // std::initializer_list<double>
    std::vector<double> v{1, 2.5};           // explicit element type; ints convert
    std::printf("%zu %zu\n", y.size(), v.size());
}
