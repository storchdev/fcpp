// std: c++17
#include <atomic>
#include <cstdio>

struct Big { long a, b, c, d; };

int main() {
    static_assert(!std::atomic<Big>::is_always_lock_free, "Big would need a lock: protect it with a mutex explicitly");
    static_assert(std::atomic<long>::is_always_lock_free, "plain integers are lock-free here");
    std::printf("checked at compile time\n");
}
