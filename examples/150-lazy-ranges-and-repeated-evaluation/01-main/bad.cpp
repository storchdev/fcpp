// std: c++20
// A transform_view computes its elements on every iteration, not once: the callable (and its side effects) runs again each pass.
#include <cstdio>
#include <ranges>
#include <vector>

int calls = 0;

int main() {
    std::vector<int> v{1, 2, 3, 4};
    auto squares = v | std::views::transform([](int x) { ++calls; return x * x; });
    long sum = 0;
    for (int s : squares) sum += s;                // pass 1: 4 calls
    for (int s : squares) sum += s;                // pass 2: 4 more calls
    std::printf("sum = %ld, transform ran %d times for 4 elements\n", sum, calls);
}
