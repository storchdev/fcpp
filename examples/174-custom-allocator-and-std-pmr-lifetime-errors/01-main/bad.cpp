// std: c++17
// sanitize: address
// A pmr container keeps a pointer to its memory resource: returning it from the scope that owns the resource leaves it dangling.
#include <cstdio>
#include <memory_resource>
#include <vector>

std::pmr::vector<int> make() {
    std::pmr::monotonic_buffer_resource pool;       // destroyed when make() returns, releasing its memory
    std::pmr::vector<int> v(&pool);
    for (int i = 0; i < 1000; ++i) v.push_back(i);
    return v;                                       // the moved vector still points at the dead pool
}

int main() {
    auto v = make();
    std::printf("v[999] = %d\n", v[999]);           // reads memory the resource already freed
}
