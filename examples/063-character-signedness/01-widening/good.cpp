// std: c++17
#include <cstdio>

int main() {
    char c = static_cast<char>(0xE9);
    unsigned char b = static_cast<unsigned char>(c);   // say what you mean: a byte value 0..255
    int widened = b;
    std::printf("widened = %d\n", widened);
    if (b == 0xE9)
        std::printf("c == 0xE9\n");
    else
        std::printf("c != 0xE9\n");
}
