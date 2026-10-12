// std: c++17
#include <cstdio>
#include <vector>

int main() {
    std::vector<bool> flags{true, false};
    bool first = flags[0];                         // convert to a real bool (a copy)
    first = false;
    std::printf("flags[0] = %d\n", (int)flags[0]);
}
