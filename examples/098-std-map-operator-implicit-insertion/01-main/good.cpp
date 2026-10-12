// std: c++17
#include <cstdio>
#include <map>
#include <string>

int main() {
    std::map<std::string, int> stock{{"apple", 3}};
    std::printf("size before = %zu\n", stock.size());
    auto it = stock.find("pear");                  // lookup without insertion (at() throws instead of inserting)
    if (it == stock.end() || it->second == 0) std::printf("pear is out of stock\n");
    std::printf("size after = %zu, contains pear: %zu\n", stock.size(), stock.count("pear"));
}
