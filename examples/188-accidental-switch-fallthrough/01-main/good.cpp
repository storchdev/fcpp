// std: c++11
#include <iostream>

enum class Charge { base, bonus };

int price(Charge charge) {
    int total = 0;
    switch (charge) {
    case Charge::base:
        total += 10;
        break;
    case Charge::bonus:
        total += 2;
        break;
    }
    return total;
}

int main() {
    std::cout << price(Charge::base) << '\n';
}
