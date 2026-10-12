// std: c++17
// expect: compile-error
// `std::vector<T>&&` is a plain rvalue reference (the parameter is not exactly `T&&`), so lvalues do not bind.
#include <string>
#include <vector>

template <class T>
void consume(std::vector<T>&& v) { (void)v; }   // not a forwarding reference

int main() {
    std::vector<std::string> names{"a", "b"};
    consume(std::vector<std::string>{"x"});   // ok: rvalue
    consume(names);                           // error: cannot bind rvalue reference to lvalue
}
