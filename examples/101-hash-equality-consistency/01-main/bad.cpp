// std: c++17
// Keys that compare equal must hash equally: here equality ignores case but the hash does not.
#include <cctype>
#include <cstdio>
#include <string>
#include <unordered_set>

struct CaseInsensitiveEq {
    bool operator()(const std::string& a, const std::string& b) const {
        if (a.size() != b.size()) return false;
        for (std::size_t i = 0; i < a.size(); ++i)
            if (std::tolower((unsigned char)a[i]) != std::tolower((unsigned char)b[i])) return false;
        return true;
    }
};

int main() {
    std::unordered_set<std::string, std::hash<std::string>, CaseInsensitiveEq> names;   // std::hash is case-sensitive
    for (int i = 0; i < 30; ++i) names.insert("name" + std::to_string(i));   // more than a small table
    names.insert("Hello");
    names.insert("HELLO");                         // equal to "Hello" under the predicate
    std::printf("size = %zu (expected 31), count(\"hello\") = %zu (expected 1)\n", names.size(), names.count("hello"));
}
