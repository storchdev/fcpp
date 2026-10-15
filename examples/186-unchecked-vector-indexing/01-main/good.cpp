// std: c++11
#include <iostream>
#include <stdexcept>
#include <vector>

int main() {
    std::vector<int> samples{10, 20, 30};
    const auto index = samples.size();
    try {
        std::cout << samples.at(index) << '\n';
    } catch (const std::out_of_range&) {
        std::cout << "invalid sample index\n";
    }
}
