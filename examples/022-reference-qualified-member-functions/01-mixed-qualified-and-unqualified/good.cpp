// std: c++17
// Qualify every overload: `const&` for lvalues, `&&` to move out of a temporary.
#include <cstdio>
#include <string>
#include <utility>

class Person {
    std::string name_ = "ada";
public:
    const std::string& name() const& { return name_; }
    std::string name() && { return std::move(name_); }
};

int main() {
    Person p;
    const std::string& a = p.name();            // const& overload: reference into p
    std::string b = Person{}.name();            // && overload: moves the string out
    std::printf("%s %s\n", a.c_str(), b.c_str());
}
