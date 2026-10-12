// expect: compile-error
// std: c++17
// Outside a template, the discarded statement of if constexpr is still fully checked.
#include <cstdio>

int main() {
    if constexpr (sizeof(int) == 4) {
        std::printf("32-bit int\n");
    } else {
        undeclared_function();                     // error: not declared, even though this branch is discarded
    }
}
