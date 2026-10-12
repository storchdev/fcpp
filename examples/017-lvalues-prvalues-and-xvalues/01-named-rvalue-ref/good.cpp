// std: c++17
// Convert the lvalue back to an xvalue with std::move at the last use; decltype((expr)) shows each category.
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

Buffer make() { return Buffer("x"); }

void take(Buffer&& b) {
    consume(b);               // still an lvalue: const& overload, the object is intact afterwards
    Sink s(std::move(b));     // xvalue: move-constructs the parameter, then moves into the member
}

int main() {
    Buffer lv("a");
    static_assert(std::is_same_v<decltype((lv)), Buffer&>);                  // lvalue
    static_assert(std::is_same_v<decltype((make())), Buffer>);               // prvalue
    static_assert(std::is_same_v<decltype((std::move(lv))), Buffer&&>);      // xvalue
    static_assert(std::is_same_v<decltype((make().data)), std::string&&>);   // member of a prvalue: xvalue
    take(Buffer("0123456789012345678901234567890123456789"));
}
