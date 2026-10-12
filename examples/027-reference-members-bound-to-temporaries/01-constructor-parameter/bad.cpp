// std: c++17
// sanitize: address
// A reference member initialized from a constructor parameter that was itself bound to a temporary.
#include <cstdio>
#include <string>

class Logger {
    const std::string& prefix_;
public:
    Logger(const std::string& prefix) : prefix_(prefix) {}   // stores a reference, not a copy
    void log(const char* msg) const { std::printf("[%s] %s\n", prefix_.c_str(), msg); }
};

int main() {
    Logger logger("a-long-enough-prefix-to-defeat-small-string-opt");   // const char* -> temporary std::string
    logger.log("started");                                              // UB: the temporary is gone
}
