// std: c++17
// Pick the bracket that matches your intent: () for "construct with these arguments", {} for "these are the elements".
#include <cstdio>
#include <memory>
#include <string>
#include <vector>

int main() {
    std::vector<int> filled(3, 7);        // count, value
    std::vector<int> elems{3, 7};         // contents
    std::string s(3, 'x');

    // Forwarding helpers always use parentheses, so the count/value meaning is preserved.
    auto p = std::make_unique<std::vector<int>>(3, 7);

    std::printf("filled=%zu elems=%zu s=%s p=%zu\n", filled.size(), elems.size(), s.c_str(), p->size());
}
