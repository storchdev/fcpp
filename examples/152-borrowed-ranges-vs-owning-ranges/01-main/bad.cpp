// std: c++20
// expect: compile-error
// ranges::find on an rvalue vector (not a borrowed range) returns std::ranges::dangling, which cannot be dereferenced.
#include <algorithm>
#include <cstdio>
#include <vector>

std::vector<int> make() { return {1, 2, 3}; }

int main() {
    auto it = std::ranges::find(make(), 2);         // returns std::ranges::dangling: the vector is gone
    std::printf("%d\n", *it);                       // error: no match for 'operator*' on std::ranges::dangling
}
