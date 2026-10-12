// std: c++17
// expect: compile-error
// Through a forwarding function, `0` and `NULL` are just int/long; they lose their null-pointer-constant status.
#include <memory>

struct Node {
    explicit Node(Node* next) : next(next) {}
    Node* next;
};

int main() {
    Node* a = new Node(0);                    // OK: literal 0 is a null pointer constant here
    auto b = std::make_unique<Node>(0);       // error: make_unique forwards `int&&`; int -> Node* is not allowed
    delete a;
}
