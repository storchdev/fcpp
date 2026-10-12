// std: c++17
// A notification is not remembered: if it is sent before the waiter blocks, and there is no state to check, the wakeup is lost.
#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <mutex>
#include <thread>

std::mutex m;
std::condition_variable cv;

int main() {
    std::thread notifier([] { cv.notify_one(); });  // runs and finishes before anyone waits
    notifier.join();
    std::unique_lock<std::mutex> lk(m);
    bool woken = cv.wait_for(lk, std::chrono::milliseconds(200)) == std::cv_status::no_timeout;   // a plain wait() would block forever
    std::printf("woken = %d\n", (int)woken);
}
