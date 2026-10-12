// std: c++17
#include <cstdio>
#include <deque>

int main() {
    std::deque<int> d{1, 2, 3};
    int& ref = d[1];                               // references to elements survive push_back
    for (int i = 0; i < 5000; ++i) d.push_back(i);
    long sum = 0;
    for (auto it = d.begin(); it != d.end(); ++it) sum += *it;   // fresh iterator
    std::printf("ref = %d, sum = %ld\n", ref, sum);
}
