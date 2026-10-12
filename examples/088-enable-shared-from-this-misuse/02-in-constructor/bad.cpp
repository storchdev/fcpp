// std: c++17
// The shared_ptr takes ownership only after the constructor returns, so shared_from_this() inside it throws.
#include <cstdio>
#include <memory>

struct Registry { void add(std::shared_ptr<struct Task>) {} };

struct Task : std::enable_shared_from_this<Task> {
    explicit Task(Registry& r) { r.add(shared_from_this()); }   // not owned yet
};

int main() {
    Registry r;
    auto t = std::make_shared<Task>(r);
    std::printf("created\n");
}
