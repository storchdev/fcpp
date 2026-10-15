// std: c++11
#include <iostream>
#include <memory>

struct Handle {
    int id = 42;
    Handle* operator&() { return nullptr; }
};

int main() {
    Handle handle;
    std::cout << std::addressof(handle)->id << '\n';
}
