// std: c++17
// std::atomic<T> compiles for any trivially copyable T but is only lock-free for small ones; large ones use a lock.
#include <atomic>
#include <cstdio>

struct Big { long a, b, c, d; };

int main() {
    std::atomic<Big> value{Big{1, 2, 3, 4}};       // compiles; no guarantee of lock-freedom
    std::atomic<long> small{0};
    std::printf("atomic<Big> is_lock_free = %d, atomic<long> is_lock_free = %d\n", (int)value.is_lock_free(), (int)small.is_lock_free());
}
