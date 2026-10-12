// std: c++17
// Give the guard a name so it lives until the end of the block.
#include <cstdio>
#include <mutex>
#include <thread>

std::mutex m;
int counter = 0;

void work() {
    for (int i = 0; i < 1000; ++i) {
        std::lock_guard<std::mutex> lock(m);
        ++counter;
    }
}

int main() {
    std::thread a(work), b(work);
    a.join();
    b.join();
    std::printf("counter = %d\n", counter);
}
