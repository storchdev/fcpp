// std: c++17
#include <cstdio>
#include <vector>

int main() {
    std::vector<int> v;
    for (int i = 0; i < 4; ++i) v.push_back(i);
    v.push_back(4);
    int& first = v[0];                             // take the reference after the last modification
    std::printf("first = %d\n", first);
    std::printf("or keep an index: v[0] = %d\n", v[0]);
}
