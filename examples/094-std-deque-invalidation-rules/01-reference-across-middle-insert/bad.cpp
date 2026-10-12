// std: c++17
// Inserting in the middle of a deque invalidates all iterators and references, unlike push_back/push_front for references.
#include <cstdio>
#include <deque>

int main() {
    std::deque<int> d{1, 2, 3};
    int& second = d[1];                            // refers to the element 2
    d.insert(d.begin() + 1, 99);                   // middle insert: all iterators and references invalidated
    std::printf("second = %d (expected 2)\n", second);
}
