// std: c++17
// A moved-from object is valid but unspecified: a defaulted move leaves scalar members untouched.
#include <cstdio>
#include <string>
#include <utility>

struct Message {
    std::string text;
    int priority = 0;                          // copied, not reset, by the defaulted move
    bool pending() const { return priority != 0; }
};

void send(Message m) { std::printf("sent '%s'\n", m.text.c_str()); }

int main() {
    Message m{"hello", 7};
    send(std::move(m));
    std::printf("after move: text size=%zu priority=%d pending=%d\n", m.text.size(), m.priority, m.pending());
    if (m.pending()) send(std::move(m));       // assumes the move cleared the message: sends it again, now empty
}
