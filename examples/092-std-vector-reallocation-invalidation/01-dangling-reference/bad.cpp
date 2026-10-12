// std: c++17
// sanitize: address
// push_back that exceeds capacity reallocates: every pointer, reference and iterator into the vector dangles.
#include <cstdio>
#include <vector>

int main() {
    std::vector<int> v;
    for (int i = 0; i < 4; ++i) v.push_back(i);   // capacity is now 4 on the implementations tried
    int& first = v[0];
    v.push_back(4);                                // size would exceed capacity: new storage, old storage freed
    std::printf("first = %d\n", first);            // use after free
}
