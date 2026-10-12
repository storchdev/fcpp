// std: c++17
// If a constructor throws, the object's own destructor does not run: cleanup written there is skipped.
#include <cstdio>
#include <stdexcept>

struct Connection {
    Connection(bool fail) {
        std::printf("open\n");
        if (fail) throw std::runtime_error("handshake failed");   // after acquiring something
    }
    ~Connection() { std::printf("close\n"); }      // only runs for fully constructed objects
};

int main() {
    try {
        Connection c(true);
    } catch (const std::exception& e) {
        std::printf("caught: %s\n", e.what());
    }
}
