// std: c++17
// Plain char may be signed or unsigned: 0xE9 widens to -23 where char is signed.
#include <cstdio>

int main() {
    char c = static_cast<char>(0xE9);          // 'é' in Latin-1
    int widened = c;                           // -23 if char is signed, 233 if unsigned
    std::printf("widened = %d\n", widened);
    if (c == 0xE9)                             // c is promoted to int first: -23 != 233
        std::printf("c == 0xE9\n");
    else
        std::printf("c != 0xE9\n");
}
