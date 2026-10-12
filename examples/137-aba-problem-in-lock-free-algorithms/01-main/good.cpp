// std: c++17
#include <atomic>
#include <cstdint>
#include <cstdio>
#include <functional>

struct Node { int value; int next; };
Node pool[3] = {{10, -1}, {20, -1}, {30, -1}};
// head packs a version tag with the index, so the value changes on every successful update
std::atomic<std::uint64_t> head{std::uint64_t(0xFFFFFFFFu)};   // tag 0, index -1

int index_of(std::uint64_t h) { return (int)(std::uint32_t)h; }
std::uint64_t make(std::uint64_t tag, int idx) { return (tag << 32) | (std::uint32_t)idx; }

void push(int idx) {
    std::uint64_t old = head.load();
    do { pool[idx].next = index_of(old); } while (!head.compare_exchange_weak(old, make((old >> 32) + 1, idx)));
}

int pop(const std::function<void()>& preempted) {
    std::uint64_t old = head.load();
    int next = pool[index_of(old)].next;
    preempted();
    while (!head.compare_exchange_weak(old, make((old >> 32) + 1, next))) next = pool[index_of(old)].next;
    return index_of(old);
}

int main() {
    push(2); push(1); push(0);
    int a = pop([] {
        int x = pop([] {});
        int y = pop([] {});
        (void)y;
        push(x);
    });
    std::printf("first pop returned node %d; head is now node %d (node 2 expected)\n", a, index_of(head.load()));
}
