// std: c++17
// `Timer t(Clock());` is parsed as a function declaration, so no Timer is ever constructed.
#include <cstdio>
#include <type_traits>

struct Clock {
    long now() const { return 42; }
};

struct Timer {
    explicit Timer(Clock c) : start(c.now()) { std::puts("Timer constructed"); }
    long start;
};

int main() {
    Timer t(Clock());   // declares `Timer t(Clock (*)())`: a function, not an object

    // t.start;         // would not compile: "request for member 'start' in 't', which is of non-class type"
    std::printf("t is a function: %d\n", std::is_function_v<decltype(t)>);
}
