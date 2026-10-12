// std: c++17
#include <atomic>
#include <cstdio>
#include <functional>
#include <mutex>
#include <vector>

struct Node { int value; Node* next; };
std::atomic<Node*> head{nullptr};
std::mutex retired_mu;
std::vector<Node*> retired;                        // unlinked nodes wait here until no reader can hold them

void push(int v) {
    Node* n = new Node{v, head.load()};
    while (!head.compare_exchange_weak(n->next, n)) {}
}

int pop(const std::function<void()>& preempted) {
    Node* old = head.load();
    preempted();
    Node* next = old->next;                        // still valid: nodes are retired, not deleted
    while (!head.compare_exchange_weak(old, next)) next = old->next;   // on failure `old` is the current head: retry
    {
        std::lock_guard<std::mutex> g(retired_mu);
        retired.push_back(old);                    // reclaim later (hazard pointers / epochs in real code)
    }
    return old->value;
}

int main() {
    push(2); push(1);
    int v = pop([] { int other = pop([] {}); (void)other; });
    std::printf("popped %d\n", v);
    for (Node* n : retired) delete n;              // safe point: no thread is inside pop()
}
