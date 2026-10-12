// std: c++17
// Guard layout assumptions with static_assert, and keep layout-sensitive types standard-layout.
#include <cstddef>
#include <cstdio>
#include <type_traits>

struct Header { int a; int b; };
static_assert(std::is_standard_layout_v<Header>);

int main() {
    std::printf("%zu\n", offsetof(Header, b));
}
