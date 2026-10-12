// std: c++17
#include <algorithm>
#include <cstdio>
#include <string>

int main() {
    const std::string longest = std::max(std::string("apple"), std::string("banana"));   // copy while the temporaries are alive
    std::printf("%s\n", longest.c_str());
}
