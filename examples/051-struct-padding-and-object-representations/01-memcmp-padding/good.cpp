// std: c++20
// Compare members (a defaulted operator== does this), and hash/serialize member by member.
#include <cstdio>

struct Key {
    char tag;
    int id;
    bool operator==(const Key&) const = default;
};

int main() {
    Key a{'x', 7}, b{'x', 7};
    std::printf("equal: %d\n", a == b);
}
