// std: c++17
// Destroying a std::thread that is still joinable calls std::terminate.
#include <cstdio>
#include <thread>

int main() {
    std::thread worker([] { std::printf("working\n"); });
    std::printf("main returning without join\n");
}                                                  // worker is joinable here
