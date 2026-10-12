// std: c++17
#include <cstdio>
#include <vector>

int main() {
    std::vector<bool> flags(8, false);
    for (auto&& f : flags) f = true;                // forwarding reference binds to the proxy temporary
    int set = 0;
    for (bool f : flags) set += f;
    std::printf("set = %d\n", set);
}
