// std: c++17
// sanitize: thread
// An unnamed std::lock_guard is a temporary: the mutex is released at the end of that statement.
#include <cstdio>
#include <mutex>
#include <thread>

std::mutex m;
int counter = 0;

void work() {
    for (int i = 0; i < 1000; ++i) {
        std::lock_guard<std::mutex>{m};   // locks and unlocks immediately
        ++counter;                         // unprotected: data race
    }
}

int main() {
    std::thread a(work), b(work);
    a.join();
    b.join();
    std::printf("counter = %d\n", counter);
}
