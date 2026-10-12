// std: c++17
// sanitize: thread
// Concurrent reads are fine, but a push_back running at the same time as any other access to the vector is a data race.
#include <cstdio>
#include <thread>
#include <vector>

int main() {
    std::vector<int> v;
    std::thread a([&] { for (int i = 0; i < 1000; ++i) v.push_back(i); });
    std::thread b([&] { for (int i = 0; i < 1000; ++i) v.push_back(-i); });
    a.join();
    b.join();
    std::printf("size = %zu (expected 2000)\n", v.size());
}
