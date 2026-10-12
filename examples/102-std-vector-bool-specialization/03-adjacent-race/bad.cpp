// std: c++17
// sanitize: thread
// Distinct elements of vector<bool> share bytes, so two threads writing different elements is a data race.
#include <cstdio>
#include <thread>
#include <vector>

int main() {
    std::vector<bool> v(2);
    std::thread a([&] { for (int i = 0; i < 100000; ++i) v[0] = true; });
    std::thread b([&] { for (int i = 0; i < 100000; ++i) v[1] = true; });   // different element, same byte
    a.join();
    b.join();
    std::printf("%d%d\n", (int)v[0], (int)v[1]);
}
