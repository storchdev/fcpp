// std: c++17
// Converting between base and derived pointers may change the address; reinterpret_cast does not adjust it.
#include <cstdio>

struct A { int a = 1; };
struct B { int b = 2; };
struct C : A, B {};                            // B's subobject lives after A's

int main() {
    C c;
    B* right = &c;                             // implicit conversion adds the offset of B
    B* wrong = reinterpret_cast<B*>(&c);       // same address as the A subobject
    std::printf("right->b = %d, wrong->b = %d\n", right->b, wrong->b);
    std::printf("offset of B in C: %td bytes\n", reinterpret_cast<char*>(right) - reinterpret_cast<char*>(&c));
}
