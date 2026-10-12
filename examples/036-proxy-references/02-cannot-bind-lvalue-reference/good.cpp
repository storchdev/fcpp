// std: c++17
// `auto&&` binds the proxy (and would bind a real bool& for other element types): the generic idiom.
#include <cstdio>
#include <vector>

int main() {
    std::vector<bool> flags{false, true};
    for (auto&& f : flags)
        f = !f;
    std::printf("%d %d\n", static_cast<bool>(flags[0]), static_cast<bool>(flags[1]));
}
