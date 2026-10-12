// std: c++17
#include <cstdio>
#include <vector>

int main() {
    std::vector<int> v{1, 2, 3};
    int visited = 0;
    for (std::size_t i = 0; i < v.size(); ++i) {   // re-evaluate size() every iteration
        if (v[i] == 2) v.push_back(9);
        if (++visited > 20) break;
    }
    std::printf("visited = %d\n", visited);
}
