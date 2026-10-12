// std: c++17
// The template argument of std::forward is the deduced type of *this* forwarding reference.
#include <cstdio>
#include <string>
#include <utility>

template <class T>
struct Slot {
    T value;
    template <class U>
    void set(U&& u) { value = std::forward<U>(u); }
};

int main() {
    Slot<std::string> slot;
    std::string name = "a-long-enough-string-to-defeat-sso-0123456789";
    slot.set(name);
    std::printf("name size after set: %zu\n", name.size());
}
