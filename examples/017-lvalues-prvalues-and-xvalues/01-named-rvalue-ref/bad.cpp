// std: c++17
// A name is an lvalue even if its type is an rvalue reference, so passing it on selects the copying overload.
#include <cstdio>
#include <string>
#include <type_traits>
#include <utility>

struct Buffer {
    std::string data;
    Buffer(std::string s) : data(std::move(s)) {}
    Buffer(const Buffer& o) : data(o.data) { std::puts("  copy"); }
    Buffer(Buffer&& o) noexcept : data(std::move(o.data)) { std::puts("  move"); }
};

struct Sink { Buffer held; explicit Sink(Buffer b) : held(std::move(b)) {} };

void consume(const Buffer&) { std::puts("consume(const Buffer&)"); }
void consume(Buffer&&)      { std::puts("consume(Buffer&&)"); }

void take(Buffer&& b) {
    static_assert(std::is_rvalue_reference_v<decltype(b)>);   // the type of b is Buffer&&...
    static_assert(std::is_lvalue_reference_v<decltype((b))>); // ...but the expression `b` is an lvalue
    consume(b);                // lvalue -> consume(const Buffer&)
    Sink s(b);                 // lvalue -> Buffer copy-constructed
}

int main() {
    take(Buffer("0123456789012345678901234567890123456789"));
}
