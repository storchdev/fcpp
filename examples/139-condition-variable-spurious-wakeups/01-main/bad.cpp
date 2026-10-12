// std: c++17
// A wait without a predicate treats any wakeup as "the condition holds"; a wakeup does not prove the state changed.
#include <condition_variable>
#include <cstdio>
#include <mutex>
#include <thread>

std::mutex m;
std::condition_variable cv;
bool ready = false;
bool waiting = false;

int main() {
    std::thread waiter([] {
        std::unique_lock<std::mutex> lk(m);
        waiting = true;
        cv.wait(lk);                               // no predicate
        std::printf("woke up, ready = %d\n", (int)ready);
    });
    for (;;) {                                     // stand-in for a spurious (or stray) wakeup: notify without changing the state
        { std::lock_guard<std::mutex> g(m); if (waiting) break; }
        std::this_thread::yield();
    }
    cv.notify_one();
    waiter.join();
}
