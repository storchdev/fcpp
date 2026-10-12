// std: c++17
#include <cstdio>
#include <deque>

int main() {
    std::deque<int> d{1, 2, 3};
    d.insert(d.begin() + 1, 99);
    int& second = d[2];                            // take the reference after the insert
    std::printf("second = %d\n", second);
}
