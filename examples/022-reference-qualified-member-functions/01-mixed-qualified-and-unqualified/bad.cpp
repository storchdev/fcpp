// std: c++17
// expect: compile-error
// If any overload of a name has a ref-qualifier, all overloads with the same parameters must have one.
#include <string>
#include <utility>

class Person {
    std::string name_ = "ada";
public:
    const std::string& name() const { return name_; }   // no ref-qualifier
    std::string name() && { return std::move(name_); }  // error: cannot be overloaded with the one above
};

int main() {
    Person p;
    (void)p.name();
}
