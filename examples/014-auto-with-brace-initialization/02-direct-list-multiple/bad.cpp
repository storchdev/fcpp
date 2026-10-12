// std: c++17
// expect: compile-error
// `auto x{1, 2}` is ill-formed (direct-list-init needs exactly one element) and `auto y = {1, 2.5}` cannot deduce one T.
#include <initializer_list>

int main() {
    auto x{1, 2};       // error: direct-list-initialization of 'auto' requires exactly one element
    auto y = {1, 2.5};  // error: unable to deduce std::initializer_list<auto> (int vs double)
    (void)x; (void)y;
}
