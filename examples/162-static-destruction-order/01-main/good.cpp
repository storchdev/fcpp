// std: c++17
#include <cstdio>
#include <string>

struct Logger {
    std::string prefix = "a prefix long enough to need heap storage, not SSO";
    void write(const char* msg) { std::printf("%s: %s\n", prefix.c_str(), msg); }
};

struct Service {
    Service();
    ~Service();
};

Logger& log() { static Logger l; return l; }

Service service;
Service::Service() { log(); }                      // construct the logger before (and so destroy it after) the service
Service::~Service() { log().write("shutting down"); }

int main() {
    log().write("starting");
}
