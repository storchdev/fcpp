// std: c++17
// sanitize: address
// memcpy copies bytes, not objects: for a non-trivially-copyable type like std::string it duplicates the owning pointer.
#include <cstdio>
#include <cstring>
#include <string>

int main() {
    alignas(std::string) unsigned char raw[sizeof(std::string)];
    std::string src(80, 'x');                       // too long for the small-string buffer: owns heap memory
    std::memcpy(raw, &src, sizeof(src));            // raw now holds a bitwise copy sharing src's buffer
    auto& copy = *reinterpret_cast<std::string*>(raw);
    std::printf("copy size = %zu\n", copy.size());
    copy.~basic_string();                           // frees the shared buffer ...
}                                                   // ... and ~src frees it again
