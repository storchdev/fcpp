// std: c++17
// vector<bool>::operator[] returns a proxy object, not bool&, so auto deduces the proxy and writes go through to the vector.
#include <cstdio>
#include <vector>

int main() {
    std::vector<bool> flags{true, false};
    auto first = flags[0];                         // a vector<bool>::reference, not a bool copy
    first = false;                                 // writes into the vector
    std::printf("flags[0] = %d (wanted the original true)\n", (int)flags[0]);
}
