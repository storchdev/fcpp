// std: c++98
// A newly visible inner name changes an unqualified call.
#include <iostream>

namespace app {
int timeout() { return 30; }

namespace test {
int timeout() { return 0; }
int request_timeout() { return timeout(); } // Finds test::timeout.
}
}

int main() {
    std::cout << app::test::request_timeout() << '\n';
}
