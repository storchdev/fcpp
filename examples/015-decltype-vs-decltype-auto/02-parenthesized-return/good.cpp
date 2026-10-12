// std: c++17
// Without parentheses decltype(id) is `int`, so the function returns by value. Plain `auto` is clearer still.
#include <cstdio>
#include <type_traits>

auto next_id() {
    int id = 41;
    ++id;
    return id;
}

int main() {
    static_assert(std::is_same_v<decltype(next_id()), int>);
    std::printf("%d\n", next_id());
}
