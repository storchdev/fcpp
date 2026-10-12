// std: c++17
// also: bad_b.cpp
// One translation unit sees `Packet` with packing 1 (as if built with different flags), the other with normal alignment.
#include <cstdio>
#include "bad_packet.h"

void fill(void* p);

int main() {
    Packet pkt{};
    fill(&pkt);
    std::printf("value = %d (expected 16909060), sizeof(Packet) = %zu\n", pkt.value, sizeof(Packet));
}
