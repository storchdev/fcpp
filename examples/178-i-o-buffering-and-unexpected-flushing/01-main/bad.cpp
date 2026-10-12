// std: c++17
// std::endl writes '\n' and then flushes: every line forces a sync with the underlying device.
#include <cstdio>
#include <iostream>
#include <streambuf>

struct CountingBuf : std::streambuf {
    long syncs = 0, bytes = 0;
    int overflow(int c) override { if (c != EOF) ++bytes; return c; }
    std::streamsize xsputn(const char*, std::streamsize n) override { bytes += n; return n; }
    int sync() override { ++syncs; return 0; }
};

int main() {
    CountingBuf buf;
    std::ostream out(&buf);
    for (int i = 0; i < 100000; ++i) out << "line " << i << std::endl;   // endl = '\n' + flush
    std::printf("flushes = %ld, bytes = %ld\n", buf.syncs, buf.bytes);
}
