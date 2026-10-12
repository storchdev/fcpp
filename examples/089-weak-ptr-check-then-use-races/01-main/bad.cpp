// std: c++17
// sanitize: undefined
// expired() then lock(): the owner can release the object in between, and lock() then returns null.
#include <cstdio>
#include <future>
#include <memory>
#include <thread>

struct Data { int value = 42; };

int main() {
    auto owner = std::make_shared<Data>();
    std::weak_ptr<Data> w = owner;

    std::promise<void> checked, released;
    std::thread other([&] {
        checked.get_future().wait();
        owner.reset();                         // the last owner lets go after the check
        released.set_value();
    });

    if (!w.expired()) {                        // true here
        checked.set_value();
        released.get_future().wait();
        std::printf("value = %d\n", w.lock()->value);   // lock() returned null: null dereference
    }
    other.join();
}
