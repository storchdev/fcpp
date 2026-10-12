// std: c++20
// sanitize: address
// A view does not own its elements: returning one over a local container leaves it pointing at freed storage.
#include <cstdio>
#include <ranges>
#include <vector>

auto doubled() {
    std::vector<int> v{1, 2, 3};
    return v | std::views::transform([](int x) { return x * 2; });   // view refers to v, which dies here
}

int main() {
    auto view = doubled();
    int first = *view.begin();                      // reads the destroyed vector's buffer
    std::printf("first = %d\n", first);
}
