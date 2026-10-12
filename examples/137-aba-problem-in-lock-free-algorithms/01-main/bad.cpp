// std: c++17
// A pointer-sized CAS cannot tell "unchanged" from "changed and changed back": here a pop succeeds with a stale `next`.
#include <atomic>
#include <cstdio>
#include <functional>

struct Node { int value; int next; };              // index-based links into a fixed pool
Node pool[3] = {{10, -1}, {20, -1}, {30, -1}};
std::atomic<int> head{-1};

void push(int idx) {
    int old = head.load();
    do { pool[idx].next = old; } while (!head.compare_exchange_weak(old, idx));
}

int pop(const std::function<void()>& preempted) {  // `preempted` models another thread running mid-pop
    int old = head.load();
    int next = pool[old].next;                     // read the successor
    preempted();                                   // ... another thread runs here ...
    while (!head.compare_exchange_weak(old, next)) next = pool[old].next;   // succeeds if head == old, even if the stack changed
    return old;
}

int main() {
    push(2); push(1); push(0);                     // stack: 0 -> 1 -> 2
    int a = pop([] {
        int x = pop([] {});                        // other thread pops node 0
        int y = pop([] {});                        // pops node 1 and keeps it
        (void)y;
        push(x);                                   // pushes node 0 back: head is 0 again, but node 1 is gone
    });
    std::printf("first pop returned node %d; head is now node %d (node 2 expected)\n", a, head.load());
}
