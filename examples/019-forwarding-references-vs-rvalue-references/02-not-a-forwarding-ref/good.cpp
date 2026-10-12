// std: c++20
// If any container should be accepted by value category, make the whole parameter the forwarding reference.
#include <concepts>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

template <class V>
    requires std::same_as<std::remove_cvref_t<V>, std::vector<std::string>>
void consume(V&& v) { std::vector<std::string> mine(std::forward<V>(v)); (void)mine; }

int main() {
    std::vector<std::string> names{"a", "b"};
    consume(std::vector<std::string>{"x"});
    consume(names);
}
