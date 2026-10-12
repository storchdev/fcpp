// std: c++20
// A lock_guard living in a coroutine frame stays locked across co_await: every other thread is blocked until the coroutine resumes.
#include <coroutine>
#include <cstdio>
#include <mutex>
#include <thread>

std::mutex m;

struct Task {
    struct promise_type {
        Task get_return_object() { return Task{std::coroutine_handle<promise_type>::from_promise(*this)}; }
        std::suspend_never initial_suspend() noexcept { return {}; }   // starts running immediately
        std::suspend_always final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };
    std::coroutine_handle<promise_type> h;
    ~Task() { if (h) h.destroy(); }
    Task(std::coroutine_handle<promise_type> hh) : h(hh) {}
    Task(Task&& o) noexcept : h(o.h) { o.h = nullptr; }
};

Task work() {
    std::lock_guard<std::mutex> lk(m);
    co_await std::suspend_always{};                 // suspended while still holding m
}

int main() {
    Task t = work();
    bool other_got_lock = false;
    std::thread other([&] { if (m.try_lock()) { other_got_lock = true; m.unlock(); } });
    other.join();
    std::printf("other thread acquired the mutex while the coroutine was suspended: %d\n", (int)other_got_lock);
    t.h.resume();                                   // must resume on the same thread that locked
}
