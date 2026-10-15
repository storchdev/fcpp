// std: c++11
// A near-matching member hides a virtual function without overriding it.
#include <iostream>

struct Renderer {
    virtual ~Renderer() = default;
    virtual int render(int scale) const { return scale; }
};

struct DetailedRenderer : Renderer {
    int render(double scale) const { return static_cast<int>(scale) * 2; }
};

int main() {
    DetailedRenderer detailed;
    Renderer& renderer = detailed;
    std::cout << renderer.render(3) << '\n'; // Calls Renderer::render.
}
