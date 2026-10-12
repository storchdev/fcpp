// std: c++17
// Obtain the pointer after the last modification, and use it before the next one.
#include <cstdio>
#include <string>

int main() {
    std::string path = "/usr/local/share/app";
    path += "/a-long-enough-suffix-to-force-reallocation-0123456789";
    std::printf("%s\n", path.c_str());
}
