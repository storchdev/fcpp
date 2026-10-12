// std: c++17
// Convert to bool explicitly to take a snapshot.
#include <cstdio>
#include <type_traits>
#include <vector>

int main() {
    std::vector<bool> flags{false, false};
    bool before = flags[0];
    static_assert(std::is_same_v<decltype(before), bool>);
    flags[0] = true;
    std::printf("saved flag = %d\n", before);
}
