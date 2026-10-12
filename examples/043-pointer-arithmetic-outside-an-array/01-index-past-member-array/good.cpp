// std: c++17
// Treat the array and the extra field separately; do not rely on member adjacency.
#include <cstdio>

struct Packet {
    int hdr[4];
    int crc;
};

int sum_all(const Packet& p) {
    int sum = p.crc;
    for (int v : p.hdr) sum += v;
    return sum;
}

int main() {
    Packet p{{1, 2, 3, 4}, 100};
    std::printf("%d\n", sum_all(p));
}
