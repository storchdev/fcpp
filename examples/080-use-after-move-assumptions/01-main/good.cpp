// std: c++17
#include <cstdio>
#include <string>
#include <utility>

struct Message {
    std::string text;
    int priority = 0;
    bool pending() const { return priority != 0; }
};

void send(Message m) { std::printf("sent '%s'\n", m.text.c_str()); }

int main() {
    Message m{"hello", 7};
    send(std::move(m));
    m = Message{};                             // reset explicitly (or don't touch m after the move)
    std::printf("after reset: pending=%d\n", m.pending());
}
