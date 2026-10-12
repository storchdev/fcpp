// std: c++17
#include <atomic>
#include <cstdio>

int main() {
    std::atomic<int> state{5};
    int expected = 0;
    const int wanted = expected;                    // keep the value you meant to compare with
    if (!state.compare_exchange_strong(expected, 1))
        std::printf("lost the race; wanted %d, found %d\n", wanted, expected);
}
