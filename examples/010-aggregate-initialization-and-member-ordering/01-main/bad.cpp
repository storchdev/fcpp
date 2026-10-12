// std: c++17
// Positional aggregate initialization depends on declaration order; reordering members silently changes meaning.
#include <cstdio>

namespace before {
struct Window { int width; int height; int border; };
}
namespace after {   // someone "tidies" the struct (alphabetical order, or groups related fields)
struct Window { int border; int height; int width; };
}

int main() {
    before::Window a{800, 600, 2};    // width=800 height=600 border=2
    after::Window  b{800, 600, 2};    // compiles unchanged: border=800 height=600 width=2
    after::Window  c{800, 600};       // trailing member is silently zero: width=0

    std::printf("a: %dx%d border=%d\n", a.width, a.height, a.border);
    std::printf("b: %dx%d border=%d\n", b.width, b.height, b.border);
    std::printf("c: %dx%d border=%d\n", c.width, c.height, c.border);
}
