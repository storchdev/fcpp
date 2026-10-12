// std: c++17
// `auto [k, v]` copies the element: modifying v changes the copy, not the container.
#include <cstdio>
#include <map>
#include <string>

int main() {
    std::map<std::string, int> counts{{"a", 1}, {"b", 2}};
    for (auto [name, n] : counts) ++n;              // n is a copy of the mapped value
    std::printf("a = %d, b = %d (expected 2 and 3)\n", counts["a"], counts["b"]);
}
