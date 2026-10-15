// std: c++11
// An overloaded unary & need not produce the object's address.
#include <iostream>

struct Handle {
    Handle* operator&() { return nullptr; }
};

int main() {
    Handle handle;
    std::cout << std::boolalpha << (&handle == nullptr) << '\n';
}
