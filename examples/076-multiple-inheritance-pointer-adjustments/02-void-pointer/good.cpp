// std: c++17
#include <cstdio>

struct A { int a = 1; };
struct B { int b = 2; };
struct C : A, B {};

void* user_data;

void callback() {
    B* b = static_cast<B*>(user_data);         // store B* and read B*: the types match
    std::printf("b->b = %d\n", b->b);
}

int main() {
    C c;
    B* as_b = &c;                              // convert to the type the callback will use, then to void*
    user_data = as_b;
    callback();
}
