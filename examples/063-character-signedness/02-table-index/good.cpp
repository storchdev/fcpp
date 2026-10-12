// std: c++17
#include <cstdio>

int main() {
    const char* text = "caf\xFF";
    int counts[256] = {};
    for (const char* p = text; *p; ++p)
        counts[static_cast<unsigned char>(*p)]++;       // always 0..255
    std::printf("%d\n", counts['c']);
}
