// std: c++17
#include <cstdio>
#include <stdexcept>

struct Handle {                                    // owns exactly one resource, so its own destructor always matches
    Handle() { std::printf("open\n"); }
    ~Handle() { std::printf("close\n"); }
};

struct Connection {
    Handle h;                                      // fully constructed member: destroyed when the constructor throws
    Connection(bool fail) {
        if (fail) throw std::runtime_error("handshake failed");
    }
};

int main() {
    try {
        Connection c(true);
    } catch (const std::exception& e) {
        std::printf("caught: %s\n", e.what());
    }
}
