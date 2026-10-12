// std: c++17
// insert takes a pair by value-like rvalue: the argument is moved into it before the key is looked up.
#include <cstdio>
#include <map>
#include <memory>

int main() {
    std::map<int, std::unique_ptr<int>> m;
    m.emplace(1, std::make_unique<int>(10));
    auto job = std::make_unique<int>(20);
    m.insert({1, std::move(job)});                 // key 1 exists: nothing is inserted, but job was already moved from
    std::printf("job is %s\n", job ? "still owned here" : "gone (null)");
}
