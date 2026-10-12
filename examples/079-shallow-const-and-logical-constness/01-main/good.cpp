// std: c++17
#include <cstdio>
#include <memory>
#include <vector>

struct Counter {
    int* count;
    explicit Counter(int* p) : count(p) {}
    std::unique_ptr<int> owned = std::make_unique<int>(0);
    std::vector<int*> slots;
    void bump() {                              // honest: not const, because it mutates
        ++*count;
        ++*owned;
        for (int* s : slots) ++*s;
    }
    int read() const { return *count + *owned; }   // a const reader that really only reads
};

int main() {
    int shared = 0, a = 0;
    Counter c(&shared);
    c.slots.push_back(&a);
    c.bump();
    const Counter& view = c;
    std::printf("shared=%d owned=%d a=%d read=%d\n", shared, *c.owned, a, view.read());
}
