// std: c++17
// Use std::forward<T> for a forwarding reference, or two plain overloads when the intent is copy vs. take.
#include <cstdio>
#include <string>
#include <utility>
#include <vector>

std::vector<std::string> log_lines;

template <class T>
void log(T&& line) {
    log_lines.push_back(std::forward<T>(line));   // copies lvalues, moves rvalues
}

int main() {
    std::string msg = "disk full";
    log(msg);
    std::printf("msg=\"%s\" (size %zu)\n", msg.c_str(), msg.size());   // intact
    log(std::string("temp"));
}
