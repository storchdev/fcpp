// std: c++98
// expect: compile-error
// A header macro also expands a standard-library member name.
#include <limits>
#include "legacy_limits.h"

int main() {
    // error: macro "max" requires 2 arguments, but only 1 given
    return std::numeric_limits<int>::max();
}
