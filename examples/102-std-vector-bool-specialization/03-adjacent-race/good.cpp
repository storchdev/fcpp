// std: c++17
#include <cstdio>
#include <thread>
#include <vector>

int main() {
    std::vector<char> v(2);                        // one byte per element: distinct elements are distinct memory locations
    std::thread a([&] { for (int i = 0; i < 100000; ++i) v[0] = 1; });
    std::thread b([&] { for (int i = 0; i < 100000; ++i) v[1] = 1; });
    a.join();
    b.join();
    std::printf("%d%d\n", (int)v[0], (int)v[1]);
}
