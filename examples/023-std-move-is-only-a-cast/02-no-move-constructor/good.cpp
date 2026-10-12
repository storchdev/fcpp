// std: c++17
// Follow the rule of zero: let the compiler generate moves. (If a destructor is needed, default the moves explicitly.)
#include <cstdio>
#include <string>
#include <utility>

struct Packet {
    std::string payload;
    explicit Packet(std::string p) : payload(std::move(p)) {}
};

int main() {
    Packet a("0123456789012345678901234567890123456789");
    Packet b = std::move(a);
    std::printf("a=%zu b=%zu\n", a.payload.size(), b.payload.size());   // 0 40 with libstdc++
}
