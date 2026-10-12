// std: c++17
// insert and emplace never overwrite an existing key; the returned bool says so, and the code ignored it.
#include <cstdio>
#include <map>

int main() {
    std::map<int, int> m{{1, 10}};
    m.insert({1, 99});                             // "update" key 1: silently does nothing
    std::printf("m[1] = %d (wanted 99)\n", m[1]);
}
