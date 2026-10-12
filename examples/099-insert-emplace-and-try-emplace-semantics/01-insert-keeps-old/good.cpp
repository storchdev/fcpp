// std: c++17
#include <cstdio>
#include <map>

int main() {
    std::map<int, int> m{{1, 10}};
    m.insert_or_assign(1, 99);                     // assigns when the key exists, inserts otherwise
    std::printf("m[1] = %d\n", m[1]);
}
