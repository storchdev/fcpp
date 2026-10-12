// std: c++17
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
        cv.wait(lk, [] { return ready; });         // re-checks the predicate after every wakeup
        std::printf("woke up, ready = %d\n", (int)ready);
    });
    for (;;) {
        { std::lock_guard<std::mutex> g(m); if (waiting) break; }
        std::this_thread::yield();
    }
    cv.notify_one();                               // stray wakeup: the waiter goes back to sleep
    { std::lock_guard<std::mutex> g(m); ready = true; }
    cv.notify_one();
    waiter.join();
}
