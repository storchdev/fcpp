// std: c++17
#include <vector>

int main() {
    std::vector<bool> v{true, false};
    for (auto&& b : v) b = false;                  // forwarding reference accepts both bool& and a proxy
}
