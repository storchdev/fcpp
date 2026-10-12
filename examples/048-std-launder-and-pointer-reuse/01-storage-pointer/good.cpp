// std: c++17
// Keep the pointer placement new returned; use std::launder only when that is not possible.
#include <cstdio>
#include <new>

struct Item { int v; };

int main() {
    alignas(Item) unsigned char buf[sizeof(Item)];
    Item* made = new (buf) Item{42};
    std::printf("%d\n", made->v);
    Item* later = std::launder(reinterpret_cast<Item*>(buf));   // valid: an Item is alive at this address
    std::printf("%d\n", later->v);
}
