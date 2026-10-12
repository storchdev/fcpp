// std: c++17
#include <cstdio>

template <class T>
struct Base {
    void hello() { std::printf("hello\n"); }
};

template <class T>
struct Derived : Base<T> {
    void run() { this->hello(); }                  // makes the call dependent: looked up at instantiation
};

int main() { Derived<int>{}.run(); }
