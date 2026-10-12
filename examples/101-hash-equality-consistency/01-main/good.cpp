// std: c++17
#include <cctype>
#include <cstdio>
#include <string>
#include <unordered_set>

struct CaseInsensitiveHash {
    std::size_t operator()(const std::string& s) const {
        std::string lower;
        for (char c : s) lower += (char)std::tolower((unsigned char)c);
        return std::hash<std::string>{}(lower);    // hash the same normalised form the equality uses
    }
};
struct CaseInsensitiveEq {
    bool operator()(const std::string& a, const std::string& b) const {
        if (a.size() != b.size()) return false;
        for (std::size_t i = 0; i < a.size(); ++i)
            if (std::tolower((unsigned char)a[i]) != std::tolower((unsigned char)b[i])) return false;
        return true;
    }
};

int main() {
    std::unordered_set<std::string, CaseInsensitiveHash, CaseInsensitiveEq> names;
    for (int i = 0; i < 30; ++i) names.insert("name" + std::to_string(i));
    names.insert("Hello");
    names.insert("HELLO");
    std::printf("size = %zu, count(\"hello\") = %zu\n", names.size(), names.count("hello"));
}
