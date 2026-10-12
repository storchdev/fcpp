// std: c++17
// A pointer stored as void* must come back as exactly the type it went in as.
#include <cstdio>

struct A { int a = 1; };
struct B { int b = 2; };
struct C : A, B {};

void* user_data;                               // e.g. the context pointer of a C callback API

void callback() {
    B* b = static_cast<B*>(user_data);         // went in as C*, comes out as B*: not the same address
    std::printf("b->b = %d\n", b->b);
}

int main() {
    C c;
    user_data = &c;                            // C* -> void*: the address of the C object, i.e. of A
    callback();
}
