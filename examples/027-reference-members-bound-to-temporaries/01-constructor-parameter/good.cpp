// std: c++17
// Store a copy (or move) of the string, so the object owns its prefix.
#include <cstdio>
#include <string>
#include <utility>

class Logger {
    std::string prefix_;
public:
    Logger(std::string prefix) : prefix_(std::move(prefix)) {}
    void log(const char* msg) const { std::printf("[%s] %s\n", prefix_.c_str(), msg); }
};

int main() {
    Logger logger("a-long-enough-prefix-to-defeat-small-string-opt");
    logger.log("started");
}
