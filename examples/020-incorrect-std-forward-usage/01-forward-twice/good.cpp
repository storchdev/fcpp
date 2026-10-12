// std: c++17
// Forward only at the last use; earlier uses take the object as an lvalue.
#include <cstdio>
#include <string>
#include <utility>

void store(const std::string& s) { std::printf("store: \"%s\"\n", s.c_str()); }
void audit(std::string s) { std::printf("audit: \"%s\"\n", s.c_str()); }

template <class T>
void record(T&& item) {
    store(item);                    // lvalue use
    audit(std::forward<T>(item));   // last use: forward
}

int main() {
    record(std::string("a-long-enough-string-to-defeat-sso-0123456789"));
}
