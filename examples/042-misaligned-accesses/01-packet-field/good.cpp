// std: c++17
// memcpy into an object of the right type: no alignment requirement on the source, and compilers emit a plain load.
#include <cstdint>
#include <cstdio>
#include <cstring>

std::uint32_t read_len(const unsigned char* pkt) {
    std::uint32_t len;
    std::memcpy(&len, pkt + 1, sizeof len);
    return len;
}

int main() {
    unsigned char pkt[8] = {0, 0x10, 0, 0, 0, 0, 0, 0};
    std::printf("%u\n", read_len(pkt));
}
