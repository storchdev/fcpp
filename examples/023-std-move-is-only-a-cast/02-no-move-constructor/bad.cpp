// std: c++17
// A user-declared destructor suppresses the implicit move constructor, so std::move silently copies.
#include <cstdio>
#include <string>
#include <utility>

struct Packet {
    std::string payload;
    explicit Packet(std::string p) : payload(std::move(p)) {}
    ~Packet() {}                          // user-declared: no implicit move ctor
};

int main() {
    Packet a("0123456789012345678901234567890123456789");
    Packet b = std::move(a);              // selects Packet(const Packet&): a copy
    std::printf("a=%zu b=%zu\n", a.payload.size(), b.payload.size());   // 40 40
}
