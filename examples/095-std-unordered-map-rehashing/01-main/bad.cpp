// std: c++17
// Rehashing invalidates iterators but not references or pointers to elements.
#include <cstdio>
#include <unordered_map>

int main() {
    std::unordered_map<int, int> m;
    for (int i = 0; i < 20; ++i) m[i] = i;
    int& ref = m[7];                               // survives rehash
    auto it = m.begin();                           // does not
    size_t before = m.bucket_count();
    for (int i = 100; i < 200; ++i) m[i] = i;      // forces a rehash
    int visited = 0;
    for (; it != m.end(); ++it) ++visited;
    std::printf("buckets %zu -> %zu, size = %zu, ref = %d\n", before, m.bucket_count(), m.size(), ref);
    std::printf("elements visited from the saved iterator: %d\n", visited);
}
