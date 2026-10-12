// std: c++17
#include <memory>

struct Node {
    explicit Node(Node* next) : next(next) {}
    Node* next;
};

int main() {
    auto a = std::make_unique<Node>(nullptr);   // nullptr_t converts to any pointer, even after forwarding
    auto b = std::make_unique<Node>(a.get());
    return b->next == a.get() ? 0 : 1;
}
