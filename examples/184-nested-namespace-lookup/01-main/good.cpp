// std: c++98
#include <iostream>

namespace app {
int timeout() { return 30; }

namespace test {
int timeout() { return 0; }
int request_timeout() { return app::timeout(); }
}
}

int main() {
    std::cout << app::test::request_timeout() << '\n';
}
