// std: c++17
#include <cstdio>

template <class T>
auto describe(const T& t) -> decltype(t.size()) { return t.size(); }   // failure in the signature is SFINAE

int describe(...) { return -1; }

int main() { std::printf("%d\n", (int)describe(5)); }
