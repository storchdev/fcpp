// std: c++17
// sanitize: address
// push_back keeps references to elements valid but invalidates every iterator.
#include <cstdio>
#include <deque>

int main() {
    std::deque<int> d{1, 2, 3};
    int& ref = d[1];                               // stays valid across push_back
    auto it = d.begin();                           // does not
    for (int i = 0; i < 5000; ++i) d.push_back(i);
    long sum = 0;
    for (; it != d.end(); ++it) sum += *it;        // walks the old internal map
    std::printf("ref = %d, sum = %ld\n", ref, sum);
}
