#include "Defines.hpp"
#include "Surface.hpp"

int main(int argc, char** argv) {
    auto surface = Surface::Create(1280, 720, "Hello");

    bool running = true;

    surface->SetCloseCallback([](Surface* surface, void* userData) -> void {
        auto running = static_cast<bool*>(userData);
        *running = false;
    }, &running);

    while (running) {
        surface->PollEvents();
    }

    return 0;
}
