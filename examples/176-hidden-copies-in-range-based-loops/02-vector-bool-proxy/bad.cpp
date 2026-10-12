// std: c++17
// expect: compile-error
// std::vector<bool> yields a proxy object by value, so `auto&` cannot bind to it.
// error: cannot bind non-const lvalue reference of type 'std::_Bit_reference&' to an rvalue of type 'std::_Bit_reference'
#include <vector>

int main() {
    std::vector<bool> flags(8, false);
    for (auto& f : flags) f = true;                 // dereferencing the iterator returns a temporary proxy
}
