// std: c++20
// sanitize: address
// A lambda coroutine's captures live in the closure object, not in the coroutine frame: if the closure dies first, the body reads freed captures.
#include <coroutine>
#include <cstdio>
#include <string>

struct Task {
    struct promise_type {
        Task get_return_object() { return Task{std::coroutine_handle<promise_type>::from_promise(*this)}; }
        std::suspend_always initial_suspend() noexcept { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };
    std::coroutine_handle<promise_type> h;
    ~Task() { if (h) h.destroy(); }
    Task(std::coroutine_handle<promise_type> hh) : h(hh) {}
    Task(Task&& o) noexcept : h(o.h) { o.h = nullptr; }
};

int main() {
    std::string text = "a captured string long enough to live on the heap, not in SSO";
    Task t = [text]() -> Task { std::printf("%s\n", text.c_str()); co_return; }();   // closure temporary dies at the semicolon
    t.h.resume();
}
