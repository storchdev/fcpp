// std: c++17
// const applies to the pointer member itself, not to what it points to.
#include <cstdio>
#include <memory>
#include <vector>

struct Counter {
    int* count;
    explicit Counter(int* p) : count(p) {}
    std::unique_ptr<int> owned = std::make_unique<int>(0);
    std::vector<int*> slots;
    void bump() const {                        // looks read-only
        ++*count;                              // modifies the pointee
        ++*owned;                              // unique_ptr's operator* is const and returns int&
        for (int* s : slots) ++*s;
    }
};

int main() {
    int shared = 0, a = 0;
    Counter c(&shared);
    c.slots.push_back(&a);
    const Counter& view = c;
    view.bump();
    std::printf("shared=%d owned=%d a=%d\n", shared, *c.owned, a);
}
