// std: c++17
// A std::map with a non-strict comparator cannot recognise equal keys: it neither deduplicates nor finds them.
#include <cstdio>
#include <functional>
#include <map>

int main() {
    std::map<int, int, std::less_equal<int>> m;
    m.insert({1, 10});
    m.insert({1, 20});                             // should have been rejected as a duplicate
    std::printf("size = %zu, count(1) = %zu, find(1) %s\n", m.size(), m.count(1), m.find(1) == m.end() ? "fails" : "succeeds");
}
