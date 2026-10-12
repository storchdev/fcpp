// std: c++17
// `{}` prefers std::initializer_list constructors, so it can mean something different from `()`.
#include <cstdio>
#include <string>
#include <vector>

int main() {
    std::vector<int> a(3, 7);   // three elements, each 7
    std::vector<int> b{3, 7};   // two elements: 3 and 7
    std::vector<int> c(5);      // five zeros
    std::vector<int> d{5};      // ONE element: 5

    std::string s(3, 'x');      // "xxx"
    std::string t{3, 'x'};      // two chars: '\x03' and 'x'

    std::printf("a.size=%zu b.size=%zu c.size=%zu d.size=%zu\n", a.size(), b.size(), c.size(), d.size());
    std::printf("s.size=%zu t.size=%zu\n", s.size(), t.size());
}
