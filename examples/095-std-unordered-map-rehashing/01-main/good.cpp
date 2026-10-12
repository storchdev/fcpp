// std: c++17
#include <cstdio>
#include <unordered_map>

int main() {
    std::unordered_map<int, int> m;
    for (int i = 0; i < 20; ++i) m[i] = i;
    int& ref = m[7];                               // references and pointers stay valid across rehash
    for (int i = 100; i < 200; ++i) m[i] = i;
    int visited = 0;
    for (auto it = m.begin(); it != m.end(); ++it) ++visited;   // get a fresh iterator afterwards
    std::printf("size = %zu, ref = %d, visited = %d\n", m.size(), ref, visited);
}
