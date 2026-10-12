// std: c++17
// `T&&` on a deduced T is a forwarding reference: it binds lvalues too, so std::move on it steals from callers.
#include <cstdio>
#include <string>
#include <utility>
#include <vector>

std::vector<std::string> log_lines;

template <class T>
void log(T&& line) {
    log_lines.push_back(std::move(line));   // intended: "take ownership of a temporary"
}

int main() {
    std::string msg = "disk full";
    log(msg);                                // compiles: T = std::string&
    std::printf("msg=\"%s\" (size %zu)\n", msg.c_str(), msg.size());   // moved-from, typically empty
    log(std::string("temp"));
}
