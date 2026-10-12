// std: c++17
// sanitize: undefined
// hdr[4] is past the end of the array even though the next member (crc) lives in the same struct.
#include <cstdio>

struct Packet {
    int hdr[4];
    int crc;
};

int sum_all(const Packet& p, int count) {
    int sum = 0;
    for (int i = 0; i < count; ++i) sum += p.hdr[i];   // count == 5 reads "hdr[4]", i.e. crc
    return sum;
}

int main(int argc, char**) {
    Packet p{{1, 2, 3, 4}, 100};
    std::printf("%d\n", sum_all(p, 4 + argc));          // argc == 1 -> count == 5
}
