// std: c++17
#include <cstdio>
#include <vector>

struct Item {
    Item() = default;
    Item(const Item&) { ++copies; }
    Item(Item&&) noexcept { ++moves; }
    static inline int copies = 0, moves = 0;
};

int main() {
    std::vector<Item> v;
    for (int i = 0; i < 100; ++i) v.emplace_back();
    std::printf("copies=%d moves=%d\n", Item::copies, Item::moves);
}
