// std: c++17
#include <cstdio>

struct File {
    bool close() { return false; }                 // report failure to the caller, who can handle it
    ~File() { close(); }                           // best-effort cleanup that never throws
};

int main() {
    File f;
    if (!f.close()) std::printf("close failed, handled by the caller\n");
}
