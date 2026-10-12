// std: c++17
#include <cstdio>
#include <stdexcept>
#include <string>
#include <utility>

struct Account {
    std::string owner;
    int balance;
    int version = 0;
};

void apply(Account& a, const std::string& new_owner, bool fail) {
    Account tmp = a;                               // work on a copy ...
    tmp.owner = new_owner;
    if (fail) throw std::runtime_error("audit log unavailable");
    ++tmp.version;
    a = std::move(tmp);                            // ... and commit with a non-throwing swap/move at the end
}

int main() {
    Account acc{"alice", 100};
    try { apply(acc, "bob", true); } catch (const std::exception&) {}
    std::printf("owner = %s, version = %d\n", acc.owner.c_str(), acc.version);
}
