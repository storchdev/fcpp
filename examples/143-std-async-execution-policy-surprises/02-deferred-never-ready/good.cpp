// std: c++17
#include <cstdio>
#include <future>

int main() {
    auto f = std::async(std::launch::async, [] { return 7; });   // ask for a thread explicitly
    std::printf("result = %d\n", f.get());
}
