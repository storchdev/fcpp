// std: c++17
#include <cstdio>
#include <future>
#include <memory>
#include <thread>

struct Data { int value = 42; };

int main() {
    auto owner = std::make_shared<Data>();
    std::weak_ptr<Data> w = owner;

    std::promise<void> locked, released;
    std::thread other([&] {
        locked.get_future().wait();
        owner.reset();
        released.set_value();
    });

    if (auto sp = w.lock()) {                  // one atomic step: either a valid owner or an empty pointer
        locked.set_value();
        released.get_future().wait();
        std::printf("value = %d\n", sp->value);   // sp keeps the object alive
    } else {
        locked.set_value();
        released.get_future().wait();
    }
    other.join();
}
