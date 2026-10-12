// std: c++20
#include <coroutine>
#include <cstdio>

struct Task {
    struct promise_type {
        Task get_return_object() { return Task{std::coroutine_handle<promise_type>::from_promise(*this)}; }
        std::suspend_always initial_suspend() noexcept { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }   // keep the frame until the owner destroys it
        void return_void() {}
        void unhandled_exception() {}
    };
    std::coroutine_handle<promise_type> h;
    ~Task() { if (h) h.destroy(); }
    Task(std::coroutine_handle<promise_type> hh) : h(hh) {}
    Task(Task&& o) noexcept : h(o.h) { o.h = nullptr; }
};

Task work() { std::puts("running"); co_return; }

int main() {
    Task t = work();
    t.h.resume();
    std::printf("done = %d\n", (int)t.h.done());
}
