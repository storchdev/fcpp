// std: c++17
// Initialize the variable, and check the result before using the out-parameter.
#include <cstdio>
#include <cstdlib>

[[gnu::noinline]] bool parse_port(const char* text, int* out) {
    char* end = nullptr;
    long v = std::strtol(text, &end, 10);
    if (end == text) return false;
    *out = static_cast<int>(v);
    return true;
}

int main(int argc, char** argv) {
    int port = 8080;                                    // default used on failure
    if (!parse_port(argc > 1 ? argv[1] : "not-a-number", &port))
        std::puts("bad port, using default");
    std::puts(port < 1024 ? "privileged port" : "unprivileged port");
}
