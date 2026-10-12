// std: c++20
// sanitize: address
// A coroutine copies its reference parameters as references: a temporary argument is gone by the time the body runs.
#include <coroutine>
#include <cstdio>
#include <string>

struct Task {
    struct promise_type {
        Task get_return_object() { return Task{std::coroutine_handle<promise_type>::from_promise(*this)}; }
        std::suspend_always initial_suspend() noexcept { return {}; }   // body does not run until resumed
        std::suspend_always final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };
    std::coroutine_handle<promise_type> h;
    ~Task() { if (h) h.destroy(); }
    Task(std::coroutine_handle<promise_type> hh) : h(hh) {}
    Task(Task&& o) noexcept : h(o.h) { o.h = nullptr; }
};

Task greet(const std::string& name) { std::printf("hello %s\n", name.c_str()); co_return; }

int main() {
    Task t = greet(std::string("a name long enough to live on the heap, not in SSO"));   // temporary destroyed at the semicolon
    t.h.resume();                                   // body reads the dead string
}
