// std: c++17
#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <mutex>
#include <thread>

std::mutex m;
std::condition_variable cv;
bool done = false;                                  // the state that the notification announces

int main() {
    std::thread notifier([] {
        { std::lock_guard<std::mutex> g(m); done = true; }   // change the state under the mutex, then notify
        cv.notify_one();
    });
    notifier.join();
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, [] { return done; });               // already true: returns immediately, whenever the notify happened
    std::printf("woken = 1\n");
}
