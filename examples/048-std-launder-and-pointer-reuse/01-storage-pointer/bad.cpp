// std: c++17
// A pointer to the storage array is not a pointer to the object created in it; std::launder (or the pointer
// returned by placement new) is needed.
#include <cstdio>
#include <new>

struct Item { int v; };

int main() {
    alignas(Item) unsigned char buf[sizeof(Item)];
    new (buf) Item{42};                               // return value discarded
    Item* p = reinterpret_cast<Item*>(buf);           // still "points to" the unsigned char array
    std::printf("%d\n", p->v);                         // UB: p does not point to the Item
}
