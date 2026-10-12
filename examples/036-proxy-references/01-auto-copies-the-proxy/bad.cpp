// std: c++17
// `auto` copies the proxy returned by vector<bool>::operator[], not the bool it stands for.
#include <cstdio>
#include <type_traits>
#include <vector>

int main() {
    std::vector<bool> flags{false, false};
    auto before = flags[0];                                   // proxy: refers to the bit inside the vector
    static_assert(!std::is_same_v<decltype(before), bool>);
    flags[0] = true;
    std::printf("saved flag = %d\n", static_cast<bool>(before));   // 1, not the 0 that was "saved"
}
