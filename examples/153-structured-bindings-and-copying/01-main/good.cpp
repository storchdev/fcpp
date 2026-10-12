// std: c++17
#include <cstdio>
#include <map>
#include <string>

int main() {
    std::map<std::string, int> counts{{"a", 1}, {"b", 2}};
    for (auto& [name, n] : counts) ++n;             // binds to the element itself
    std::printf("a = %d, b = %d (expected 2 and 3)\n", counts["a"], counts["b"]);
}
