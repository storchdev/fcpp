// std: c++17
#include <cstdio>

struct A { int a = 1; };
struct B { int b = 2; };
struct C : A, B {};

int main() {
    C c;
    B* right = static_cast<B*>(&c);            // static_cast (or an implicit conversion) applies the adjustment
    C* back = static_cast<C*>(right);          // and undoes it
    std::printf("right->b = %d, back == &c: %d\n", right->b, back == &c);
}
