// std: c++20
// sanitize: address
// A coroutine_handle does not own the frame: destroying it both through the owner and by hand frees it twice.
#include <coroutine>
#include <cstdio>

struct Task {
    struct promise_type {
        Task get_return_object() { return Task{std::coroutine_handle<promise_type>::from_promise(*this)}; }
        std::suspend_always initial_suspend() noexcept { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };
    std::coroutine_handle<promise_type> h;
    ~Task() { if (h) h.destroy(); }                 // the owner frees the frame
    Task(std::coroutine_handle<promise_type> hh) : h(hh) {}
    Task(Task&& o) noexcept : h(o.h) { o.h = nullptr; }
};

Task work() { std::puts("running"); co_return; }

int main() {
    Task t = work();
    t.h.resume();
    t.h.destroy();                                  // manual destroy ...
}                                                   // ... and ~Task destroys it again
