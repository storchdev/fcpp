// std: c++20
#include <cstdio>
#include <ranges>
#include <vector>

int calls = 0;

int main() {
    std::vector<int> v{1, 2, 3, 4};
    auto lazy = v | std::views::transform([](int x) { ++calls; return x * x; });
    std::vector<int> squares(lazy.begin(), lazy.end());   // evaluate once and keep the results
    long sum = 0;
    for (int s : squares) sum += s;
    for (int s : squares) sum += s;
    std::printf("sum = %ld, transform ran %d times for 4 elements\n", sum, calls);
}
