// std: c++17
// Provide an `&&` overload that returns by value, so a chain started on a temporary stays valid.
#include <cstdio>
#include <string>
#include <utility>

class Builder {
    std::string text_;
public:
    Builder& add(const std::string& s) & { text_ += s; return *this; }
    Builder&& add(const std::string& s) && { text_ += s; return std::move(*this); }
    std::string str() const { return text_; }
};

Builder make_builder() { return Builder{}; }

int main() {
    Builder b;
    b.add("x");
    std::string s = make_builder().add("y").add("z").str();
    std::printf("%s %s\n", b.str().c_str(), s.c_str());
}
