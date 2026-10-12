// std: c++17
// Overload resolution ignores explicit specializations; it picks a template first, then uses that template's specialization.
#include <cstdio>

template <class T> void f(T) { std::printf("f(T)\n"); }          // #1
template <> void f<int*>(int*) { std::printf("f<int*> specialization of #1\n"); }
template <class T> void f(T*) { std::printf("f(T*)\n"); }        // #2: declared after the specialization

int main() {
    int x = 0;
    f(&x);                                         // #2 is the better template, so #1's specialization is never used
}
