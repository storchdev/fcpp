// std: c++17
// operator[] inserts a value-initialized element when the key is missing, even in a "read-only" lookup.
#include <cstdio>
#include <map>
#include <string>

int main() {
    std::map<std::string, int> stock{{"apple", 3}};
    std::printf("size before = %zu\n", stock.size());
    if (stock["pear"] == 0) std::printf("pear is out of stock\n");   // inserts "pear" -> 0
    std::printf("size after = %zu, contains pear: %zu\n", stock.size(), stock.count("pear"));
}
