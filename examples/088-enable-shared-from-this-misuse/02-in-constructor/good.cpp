// std: c++17
#include <cstdio>
#include <memory>

struct Registry { void add(std::shared_ptr<struct Task>) {} };

struct Task : std::enable_shared_from_this<Task> {
    static std::shared_ptr<Task> create(Registry& r) {   // factory: register after the shared_ptr exists
        auto t = std::shared_ptr<Task>(new Task);
        r.add(t->shared_from_this());
        return t;
    }
private:
    Task() = default;
};

int main() {
    Registry r;
    auto t = Task::create(r);
    std::printf("created\n");
}
