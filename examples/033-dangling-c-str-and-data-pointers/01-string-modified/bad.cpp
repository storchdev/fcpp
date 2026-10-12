// std: c++17
// sanitize: address
// Appending can reallocate the string's buffer, invalidating pointers obtained earlier.
#include <cstdio>
#include <string>

int main() {
    std::string path = "/usr/local/share/app";
    const char* c = path.c_str();                       // points at the current buffer
    path += "/a-long-enough-suffix-to-force-reallocation-0123456789";
    std::printf("%s\n", c);                             // UB: heap-use-after-free
}
