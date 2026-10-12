// expect: compile-error
// std: c++17
// vector<bool> holds bits, so there is no bool& to bind to: generic code that takes a reference breaks.
// g++:     error: cannot bind non-const lvalue reference of type ‘std::_Bit_reference&’ to an rvalue of type ‘std::_Bit_iterator::reference’
// clang++: error: non-const lvalue reference to type 'reference' (aka '_Bit_reference') cannot bind to a temporary of type 'reference' (aka '_Bit_reference')
#include <vector>

int main() {
    std::vector<bool> v{true, false};
    for (auto& b : v) b = false;
}
