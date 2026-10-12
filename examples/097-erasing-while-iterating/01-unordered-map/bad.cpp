// std: c++17
// sanitize: address
// erase(it) invalidates it; the loop's ++it then advances an erased element.
#include <cstdio>
#include <unordered_map>

int main() {
    std::unordered_map<int, int> m;
    for (int i = 0; i < 10; ++i) m[i] = i;
    for (auto it = m.begin(); it != m.end(); ++it)
        if (it->first % 2 == 0) m.erase(it);       // it is invalid after this call
    std::printf("size = %zu\n", m.size());
}
