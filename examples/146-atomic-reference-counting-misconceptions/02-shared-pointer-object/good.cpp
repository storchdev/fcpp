// std: c++20
#include <atomic>
#include <cstdio>
#include <memory>
#include <thread>

std::atomic<std::shared_ptr<int>> global{std::make_shared<int>(1)};   // C++20: atomic access to the pointer itself

int main() {
    std::thread writer([] { for (int i = 0; i < 200000; ++i) global.store(std::make_shared<int>(i)); });
    long sum = 0;
    std::thread reader([&] { for (int i = 0; i < 200000; ++i) sum += *global.load(); });
    writer.join();
    reader.join();
    std::printf("done, sum = %ld\n", sum);
}
