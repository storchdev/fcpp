// std: c++17
#include <chrono>
#include <cstdio>
#include <future>
#include <thread>

int main() {
    auto f = std::async(std::launch::async, [] {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::printf("task finished\n");
    });
    std::printf("launched\n");                     // runs while the task is still sleeping
    f.get();
}
