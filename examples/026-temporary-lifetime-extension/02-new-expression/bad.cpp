// std: c++20
// sanitize: address
// A temporary bound to a reference member inside a new-expression is destroyed at the end of the full-expression.
#include <cstdio>
#include <string>

struct Label { const std::string& text; };

int main() {
    Label on_stack{std::string("a-long-enough-string-to-defeat-sso-0123456789")};              // aggregate init of a named object: extended
    const Label* heap = new Label{std::string("a-long-enough-string-to-defeat-sso-0123456789")};   // new-initializer: NOT extended
    std::printf("%s\n", on_stack.text.c_str());
    std::printf("%s\n", heap->text.c_str());         // UB: the string died at the ';' above
    delete heap;
}
