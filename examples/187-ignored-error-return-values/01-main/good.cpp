// std: c++17
#include <iostream>

[[nodiscard]] bool save_config() { return false; }

int main() {
    if (!save_config()) {
        std::cout << "configuration could not be saved\n";
        return 0;
    }
    std::cout << "configuration saved\n";
}
