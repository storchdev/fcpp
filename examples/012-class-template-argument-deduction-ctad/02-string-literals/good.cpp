// std: c++17
// Name the element type, or use a string literal operator so the literal already is a std::string.
#include <cstdio>
#include <string>
#include <type_traits>
#include <vector>

using namespace std::string_literals;

int main() {
    std::vector<std::string> names{"bob", "alice"};
    std::vector more{"bob"s, "alice"s};      // CTAD with std::string
    static_assert(std::is_same_v<decltype(more), std::vector<std::string>>);

    std::printf("names[0] == \"bob\"? %d\n", names[0] == "bob");
}
