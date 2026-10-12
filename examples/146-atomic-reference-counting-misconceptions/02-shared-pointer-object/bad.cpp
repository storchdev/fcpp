// std: c++20
// sanitize: thread
// Only the control block is thread-safe: reassigning the same shared_ptr object from two threads is a data race.
#include <cstdio>
#include <memory>
#include <thread>

std::shared_ptr<int> global = std::make_shared<int>(1);

int main() {
    std::thread writer([] { for (int i = 0; i < 200000; ++i) global = std::make_shared<int>(i); });
    long sum = 0;
    std::thread reader([&] { for (int i = 0; i < 200000; ++i) sum += *global; });
    writer.join();
    reader.join();
    std::printf("done, sum = %ld\n", sum);
}
