// std: c++20
#include <cstdio>
#include <thread>

int main() {
    std::jthread worker([] { std::printf("working\n"); });   // joins in its destructor
    std::printf("main returning\n");
}
