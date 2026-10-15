// std: c++98
#include <iostream>

int main() {
    int limit = 7;
    const int& view = limit;
    limit = 9; // Mutate through the original, non-const access path.
    std::cout << "limit=" << view << '\n';
}
