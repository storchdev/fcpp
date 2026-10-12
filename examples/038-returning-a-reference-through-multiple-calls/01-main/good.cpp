// std: c++17
// Return by value at the point where ownership is needed; callers up the chain then hold a real object.
#include <cstdio>
#include <string>
#include <vector>

std::vector<std::string> load_names() { return {"alice-long-enough-to-defeat-sso-0123456789", "bob"}; }

const std::string& first(const std::vector<std::string>& v) { return v.front(); }

std::string default_name() { return first(load_names()); }   // copies while the vector is still alive

int main() {
    std::printf("%s\n", default_name().c_str());
}
