// std: c++17
// sanitize: undefined
// Casting a byte pointer to uint32_t* is UB unless the address is aligned for uint32_t.
#include <cstdint>
#include <cstdio>

std::uint32_t read_len(const unsigned char* pkt) {
    return *reinterpret_cast<const std::uint32_t*>(pkt + 1);   // header byte, then a 4-byte field at offset 1
}

int main() {
    unsigned char pkt[8] = {0, 0x10, 0, 0, 0, 0, 0, 0};
    std::printf("%u\n", read_len(pkt));
}
