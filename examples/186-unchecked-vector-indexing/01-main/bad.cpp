// std: c++11
// operator[] does not check whether the index names an element.
// sanitize: address
#include <iostream>
#include <vector>

int main() {
    std::vector<int> samples{10, 20, 30};
    const auto index = samples.size();
    std::cout << samples[index] << '\n'; // One past the final element.
}
