// std: c++17
// sanitize: address
// Unlinking a node atomically does not mean no other thread still holds a pointer to it.
#include <atomic>
#include <cstdio>
#include <functional>

struct Node { int value; Node* next; };
std::atomic<Node*> head{nullptr};

void push(int v) {
    Node* n = new Node{v, head.load()};
    while (!head.compare_exchange_weak(n->next, n)) {}
}

int pop(const std::function<void()>& preempted) {
    Node* old = head.load();
    preempted();                                   // another thread runs after we loaded `old` ...
    Node* next = old->next;                        // ... and may already have freed it
    head.compare_exchange_strong(old, next);
    int v = old->value;
    delete old;
    return v;
}

int main() {
    push(2); push(1);
    int v = pop([] { int other = pop([] {}); (void)other; });   // other thread pops and deletes the same node
    std::printf("popped %d\n", v);
}
