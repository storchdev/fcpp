// std: c++17
// also: good_b.cpp
#include <cstdio>
#include "good_packet.h"

void fill(void* p);

int main() {
    Packet pkt{};
    fill(&pkt);
    std::printf("value = %d (expected 16909060), sizeof(Packet) = %zu\n", pkt.value, sizeof(Packet));
}
