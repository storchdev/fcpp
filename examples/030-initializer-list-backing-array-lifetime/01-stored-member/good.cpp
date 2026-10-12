// std: c++17
// Copy the elements into an owning container.
#include <cstdio>
#include <initializer_list>
#include <vector>

struct Samples {
    std::vector<int> values;
    Samples(std::initializer_list<int> v) : values(v) {}
};

int main(int argc, char**) {
    Samples s{argc, argc + 1, argc + 2};
    std::printf("%d\n", s.values.front());
}
