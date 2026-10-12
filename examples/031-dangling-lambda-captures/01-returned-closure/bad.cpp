// std: c++17
// sanitize: address
// A closure that captures a local by reference must not outlive that local.
#include <cstdio>
#include <functional>

std::function<int()> make_counter(int start) {
    int count = start;
    return [&count] { return ++count; };   // captures the local 'count' by reference; dies when make_counter returns
}

int main() {
    auto next = make_counter(10);
    std::printf("%d\n", next());            // UB: stack-use-after-return
}
