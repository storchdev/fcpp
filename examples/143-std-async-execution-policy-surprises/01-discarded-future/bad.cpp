// std: c++17
// The future returned by std::async(launch::async, ...) joins in its destructor: discarding it makes the call synchronous.
#include <chrono>
#include <cstdio>
#include <future>
#include <thread>

int main() {
    std::async(std::launch::async, [] {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::printf("task finished\n");
    });                                            // temporary future destroyed here: blocks until the task ends
    std::printf("launched\n");
}
