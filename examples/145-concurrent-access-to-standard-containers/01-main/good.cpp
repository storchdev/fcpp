// std: c++17
#include <cstdio>
#include <mutex>
#include <thread>
#include <vector>

int main() {
    std::vector<int> v;
    std::mutex m;
    auto work = [&](int sign) { for (int i = 0; i < 1000; ++i) { std::lock_guard<std::mutex> g(m); v.push_back(sign * i); } };
    std::thread a(work, 1), b(work, -1);
    a.join();
    b.join();
    std::printf("size = %zu (expected 2000)\n", v.size());
}
