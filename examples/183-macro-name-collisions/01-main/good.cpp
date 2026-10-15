// std: c++98
#include <limits>
#include "legacy_limits.h"
#undef max

int main() {
    return std::numeric_limits<int>::max() > 0 ? 0 : 1;
}
