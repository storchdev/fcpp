// std: c++17
#include <cstdio>

template <class T> struct Name { static const char* get() { return "generic"; } };
template <> struct Name<int> { static const char* get() { return "int"; } };   // before any use

const char* first() { return Name<int>::get(); }

int main() { std::printf("%s\n", first()); }
