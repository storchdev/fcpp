// std: c++17
// sanitize: address
// A plain char used as an array index is negative when char is signed and the byte is >= 0x80.
#include <cstdio>
#include <cstring>

int main() {
    const char* text = "caf\xFF";               // Latin-1 'ÿ' is 0xFF
    int counts[256] = {};
    for (const char* p = text; *p; ++p)
        counts[*p]++;                            // *p is -1 for 0xFF where char is signed: counts[-1]
    std::printf("%d\n", counts['c']);
}
