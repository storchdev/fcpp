// std: c++17
#include <cstdio>
#include <unordered_map>

int main() {
    std::unordered_map<int, int> m;
    for (int i = 0; i < 10; ++i) m[i] = i;
    for (auto it = m.begin(); it != m.end();) {
        if (it->first % 2 == 0) it = m.erase(it);  // erase returns the next valid iterator
        else ++it;
    }
    std::printf("size = %zu\n", m.size());
}
