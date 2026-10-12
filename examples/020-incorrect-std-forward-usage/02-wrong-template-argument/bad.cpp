// std: c++17
// Forwarding with the class's T instead of the member template's own U turns every argument into an rvalue.
#include <cstdio>
#include <string>
#include <utility>

template <class T>
struct Slot {
    T value;
    template <class U>
    void set(U&& u) { value = std::forward<T>(u); }   // should be std::forward<U>(u)
};

int main() {
    Slot<std::string> slot;
    std::string name = "a-long-enough-string-to-defeat-sso-0123456789";
    slot.set(name);   // U = std::string&, but forward<std::string> casts to std::string&&
    std::printf("name size after set: %zu\n", name.size());
}
