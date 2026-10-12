// std: c++17
// expect: compile-error
// vector<bool>::operator[] returns a prvalue proxy, which cannot bind to a non-const lvalue reference.
#include <vector>

int main() {
    std::vector<bool> flags{false, true};
    for (auto& f : flags)      // error: cannot bind non-const lvalue reference to an rvalue
        f = !f;
}
