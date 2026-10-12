// std: c++17
#include <cstdio>
#include <functional>
#include <map>

int main() {
    std::map<int, int, std::less<int>> m;
    m.insert({1, 10});
    m.insert({1, 20});
    std::printf("size = %zu, count(1) = %zu, find(1) %s\n", m.size(), m.count(1), m.find(1) == m.end() ? "fails" : "succeeds");
}
