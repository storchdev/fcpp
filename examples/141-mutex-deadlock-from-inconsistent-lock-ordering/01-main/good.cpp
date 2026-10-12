// std: c++17
#include <cstdio>
#include <mutex>
#include <thread>

std::mutex a, b;

int main() {
    std::thread t1([] { std::scoped_lock lk(a, b); });   // deadlock-avoiding acquisition of both
    std::thread t2([] { std::scoped_lock lk(b, a); });   // order of the arguments does not matter
    t1.join();
    t2.join();
    std::printf("finished\n");
}
