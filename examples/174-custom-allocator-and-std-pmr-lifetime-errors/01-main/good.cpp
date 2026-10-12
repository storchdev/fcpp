// std: c++17
#include <cstdio>
#include <memory_resource>
#include <vector>

int main() {
    std::pmr::monotonic_buffer_resource pool;       // declared before, and so destroyed after, everything that uses it
    std::pmr::vector<int> v(&pool);
    for (int i = 0; i < 1000; ++i) v.push_back(i);
    std::printf("v[999] = %d\n", v[999]);
}
