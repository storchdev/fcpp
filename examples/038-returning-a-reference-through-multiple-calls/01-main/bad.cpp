// std: c++17
// sanitize: address
// Each function forwards a reference "safely", but the object at the bottom of the chain is a temporary.
#include <cstdio>
#include <string>
#include <vector>

std::vector<std::string> load_names() { return {"alice-long-enough-to-defeat-sso-0123456789", "bob"}; }

const std::string& first(const std::vector<std::string>& v) { return v.front(); }

const std::string& default_name() { return first(load_names()); }   // the vector dies at the end of this statement

int main() {
    std::printf("%s\n", default_name().c_str());    // UB: heap-use-after-free
}
