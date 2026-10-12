// std: c++17
// On failure the expected-value argument is overwritten with the value actually found.
#include <atomic>
#include <cstdio>

int main() {
    std::atomic<int> state{5};                      // someone else already moved it from 0
    int expected = 0;
    if (!state.compare_exchange_strong(expected, 1))
        std::printf("lost the race; state was %d, but expected now reads %d\n", 0, expected);   // the code assumed it was still 0
}
