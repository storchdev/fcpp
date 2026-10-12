// std: c++17
// offsetof is only required to work for standard-layout types; elsewhere it is conditionally supported.
#include <cstddef>
#include <cstdio>
#include <type_traits>

struct Base { int a; };
struct Derived : Base { int b; };        // data members in both Base and Derived
struct Poly { int x; virtual void f() {} };
struct Mixed { int pub; private: int priv; };   // different access control on non-static members

static_assert(!std::is_standard_layout_v<Derived>);
static_assert(!std::is_standard_layout_v<Poly>);
static_assert(!std::is_standard_layout_v<Mixed>);

int main() {
    std::printf("%zu\n", offsetof(Derived, b));   // conditionally supported
    std::printf("%zu\n", offsetof(Poly, x));      // conditionally supported
}
