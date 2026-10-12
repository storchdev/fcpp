// std: c++17
// Always spell a null pointer `nullptr`.
#include <cstdio>

void report(int)         { std::puts("report(int)"); }
void report(const char*) { std::puts("report(const char*)"); }
void assign(long)        { std::puts("assign(long)"); }
void assign(const char*) { std::puts("assign(const char*)"); }

int main() {
    report(nullptr);
    assign(nullptr);
    const char* p = nullptr;
    report(p);
}
