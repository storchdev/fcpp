// std: c++20
// sanitize: address
// With final_suspend = suspend_never, the frame is destroyed when the coroutine finishes; the handle then dangles.
#include <coroutine>
#include <cstdio>

struct Task {
    struct promise_type {
        Task get_return_object() { return Task{std::coroutine_handle<promise_type>::from_promise(*this)}; }
        std::suspend_always initial_suspend() noexcept { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }   // frame freed right after the body ends
        void return_void() {}
        void unhandled_exception() {}
    };
    std::coroutine_handle<promise_type> h;
};

Task work() { std::puts("running"); co_return; }

int main() {
    Task t = work();
    t.h.resume();                                   // runs to completion and frees the frame
    std::printf("done = %d\n", (int)t.h.done());    // reads the destroyed frame
}
