// std: c++17
#include <cstdio>
#include <map>
#include <memory>

int main() {
    std::map<int, std::unique_ptr<int>> m;
    m.emplace(1, std::make_unique<int>(10));
    auto job = std::make_unique<int>(20);
    m.try_emplace(1, std::move(job));              // guaranteed: if the key exists, job is not moved from
    std::printf("job is %s\n", job ? "still owned here" : "gone (null)");
}
