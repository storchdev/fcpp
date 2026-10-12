// std: c++17
// sanitize: memory
// An out-parameter that is written on only some paths leaves the caller's variable indeterminate.
#include <cstdio>
#include <cstdlib>

[[gnu::noinline]] bool parse_port(const char* text, int* out) {
    char* end = nullptr;
    long v = std::strtol(text, &end, 10);
    if (end == text) return false;     // failure: *out is never written
    *out = static_cast<int>(v);
    return true;
}

int main(int argc, char** argv) {
    int port;                                           // default-initialized: indeterminate
    parse_port(argc > 1 ? argv[1] : "not-a-number", &port);   // return value ignored
    if (port < 1024)                                    // UB on failure: branches on an indeterminate value
        std::puts("privileged port");
    else
        std::puts("unprivileged port");
}
