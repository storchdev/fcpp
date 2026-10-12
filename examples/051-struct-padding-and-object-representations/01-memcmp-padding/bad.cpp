// std: c++17
// Equal field values do not imply equal bytes: padding bytes are unspecified.
#include <cstdio>
#include <cstring>
#include <type_traits>

struct Key {
    char tag;     // 3 padding bytes follow (on this ABI)
    int id;
};
static_assert(sizeof(Key) == 8);   // 1 + 3 padding + 4
static_assert(!std::has_unique_object_representations_v<Key>);

[[gnu::noinline]] void fill(Key& k, int fill_byte) {
    std::memset(&k, fill_byte, sizeof k);   // stands in for stale stack/heap contents
    k.tag = 'x';
    k.id = 7;
}

int main() {
    Key a, b;
    fill(a, 0x00);
    fill(b, 0xFF);
    std::printf("fields equal: %d, memcmp equal: %d\n", a.tag == b.tag && a.id == b.id,
                std::memcmp(&a, &b, sizeof a) == 0);
}
