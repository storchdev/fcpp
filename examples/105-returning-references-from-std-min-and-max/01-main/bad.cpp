// std: c++17
// sanitize: address
// std::max returns a reference to one of its arguments; with temporaries it dangles at the end of the full-expression.
#include <algorithm>
#include <cstdio>
#include <string>

int main() {
    const std::string& longest = std::max(std::string("apple"), std::string("banana"));
    std::printf("%s\n", longest.c_str());          // both temporaries are already destroyed
}
