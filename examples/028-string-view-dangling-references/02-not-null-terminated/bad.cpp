// std: c++17
// sanitize: address
// string_view is (pointer, length), not a C string: data() need not be null-terminated.
#include <cstdio>
#include <string_view>

int main() {
    const char buf[3] = {'a', 'b', 'c'};          // no terminator
    std::string_view sv(buf, 3);
    std::printf("%s\n", sv.data());               // UB: %s reads past the end of buf
}
