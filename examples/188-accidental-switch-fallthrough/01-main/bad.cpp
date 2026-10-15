// std: c++11
// A missing break executes the next case too.
#include <iostream>

enum class Charge { base, bonus };

int price(Charge charge) {
    int total = 0;
    switch (charge) {
    case Charge::base:
        total += 10;
        // Missing break: the bonus is charged as well.
    case Charge::bonus:
        total += 2;
        break;
    }
    return total;
}

int main() {
    std::cout << price(Charge::base) << '\n';
}
