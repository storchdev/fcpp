// std: c++20
#include <cstdio>
#include <ranges>
#include <vector>

std::vector<int> doubled() {
    std::vector<int> v{1, 2, 3};
    std::vector<int> out;
    for (int x : v | std::views::transform([](int x) { return x * 2; })) out.push_back(x);
    return out;                                     // return the data, not a view of local data
}

int main() {
    auto result = doubled();
    std::printf("first = %d\n", result.front());
}
