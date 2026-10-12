// std: c++17
// std::forward<T>(x) is an rvalue cast for rvalue arguments: using it twice reads a moved-from object.
#include <cstdio>
#include <string>
#include <utility>

void store(std::string s) { std::printf("store: \"%s\"\n", s.c_str()); }
void audit(std::string s) { std::printf("audit: \"%s\"\n", s.c_str()); }

template <class T>
void record(T&& item) {
    store(std::forward<T>(item));   // for an rvalue argument: moves from item
    audit(std::forward<T>(item));   // item is now moved-from
}

int main() {
    record(std::string("a-long-enough-string-to-defeat-sso-0123456789"));
}
