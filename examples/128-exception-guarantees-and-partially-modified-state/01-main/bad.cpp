// std: c++17
// Without the strong guarantee, an exception between two writes leaves the object half-updated.
#include <cstdio>
#include <stdexcept>
#include <string>

struct Account {
    std::string owner;
    int balance;
    int version = 0;
};

void apply(Account& a, const std::string& new_owner, bool fail) {
    a.owner = new_owner;                           // committed
    if (fail) throw std::runtime_error("audit log unavailable");
    ++a.version;                                   // never reached
}

int main() {
    Account acc{"alice", 100};
    try { apply(acc, "bob", true); } catch (const std::exception&) {}
    std::printf("owner = %s, version = %d (owner changed but version did not)\n", acc.owner.c_str(), acc.version);
}
