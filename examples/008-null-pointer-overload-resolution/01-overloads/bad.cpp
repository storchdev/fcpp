// std: c++17
// 0 and NULL are integers; only nullptr is a null pointer that prefers the pointer overload.
#include <cstddef>
#include <cstdio>

void report(int)         { std::puts("report(int)"); }
void report(const char*) { std::puts("report(const char*)"); }
void assign(long)        { std::puts("assign(long)"); }
void assign(const char*) { std::puts("assign(const char*)"); }

int main() {
    report(0);          // report(int): an exact match beats the null pointer conversion
    assign(NULL);       // assign(long): NULL is an integer constant here (g++ warns: -Wconversion-null)
    // report(NULL);    // error: ambiguous on both g++ and clang++ (int and pointer both need a conversion)
    assign(nullptr);    // assign(const char*)
}
