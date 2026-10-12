// std: c++17
// CTAD deduces from the argument types as written: string literals become const char*, not std::string.
#include <cstdio>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

int main() {
    std::vector names{"bob", "alice"};      // vector<const char*>
    std::pair entry{"id", 42};              // pair<const char*, int>
    static_assert(std::is_same_v<decltype(names), std::vector<const char*>>);
    static_assert(std::is_same_v<decltype(entry), std::pair<const char*, int>>);

    // Comparing const char* compares addresses, not text: equal text in different storage is "not equal".
    std::string input = "bob";
    std::printf("names[0] == input.c_str()? %d (address comparison)\n", names[0] == input.c_str());

    // The parenthesized form selects the iterator-pair deduction guide instead (never run this):
    static_assert(std::is_same_v<decltype(std::vector("bob", "alice")), std::vector<char>>);
}
