// std: c++17
// expect: compile-error
// An `&`-qualified member can only be called on lvalues; with no `&&` overload a temporary has no viable function.
#include <string>

class Builder {
    std::string text_;
public:
    Builder& add(const std::string& s) & { text_ += s; return *this; }
    std::string str() const { return text_; }
};

Builder make_builder() { return Builder{}; }

int main() {
    Builder b;
    b.add("x");                       // ok: lvalue
    make_builder().add("y");          // error: 'this' argument ... is an rvalue, but function has non-const lvalue ref-qualifier (clang++)
}
