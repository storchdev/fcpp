// std: c++17
// An ignored failure result lets the caller report success.
#include <iostream>

bool save_config() { return false; }

int main() {
    save_config(); // Failure is discarded.
    std::cout << "configuration saved\n";
}
