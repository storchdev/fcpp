// expect: compile-error
// std: c++17
// An explicit specialization must be declared before the first use that would instantiate the primary template.
#include <cstdio>

template <class T> struct Name { static const char* get() { return "generic"; } };

const char* first() { return Name<int>::get(); }   // implicitly instantiates Name<int>

template <> struct Name<int> { static const char* get() { return "int"; } };   // error: specialization after instantiation

int main() { std::printf("%s\n", first()); }
