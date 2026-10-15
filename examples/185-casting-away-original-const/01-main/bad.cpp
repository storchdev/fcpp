// std: c++98
// Removing const does not make an originally const object writable.
#include <iostream>

int main() {
    const int limit = 7;
    const int& view = limit;
    int& writable = const_cast<int&>(view);
    writable = 9; // Undefined behavior: limit was declared const.
    std::cout << "limit=" << limit << ", through reference=" << writable << '\n';
}
