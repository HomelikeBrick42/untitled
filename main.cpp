#include "Defines.hpp"
#include "Surface.hpp"
#include "OpenGLRenderContext.hpp"

int main() {
    auto surface1 = Surface::Create(640, 480, "Window 1");
    auto context1 = RenderContext::Create(surface1.get(), RendererAPI::OpenGL);
    auto openglContext1 = dynamic_cast<OpenGLRenderContext*>(context1.get());

    auto surface2 = Surface::Create(640, 480, "Window 2");
    auto context2 = RenderContext::Create(surface2.get(), RendererAPI::OpenGL);
    auto openglContext2 = dynamic_cast<OpenGLRenderContext*>(context2.get());

    bool running = true;

    auto closeCallback = [](Surface* surface, void* userData) -> void {
        auto running = static_cast<bool*>(userData);
        *running = false;
    };

    surface1->SetCloseCallback(closeCallback, &running);
    surface2->SetCloseCallback(closeCallback, &running);

    while (running) {
        openglContext1->glClearColor(0.1, 0.1, 0.1, 1.0);
        openglContext1->glClear(GL_COLOR_BUFFER_BIT);

        context1->SwapBuffers();
        surface1->PollEvents();

        openglContext2->glClearColor(1.0, 0.0, 0.0, 1.0);
        openglContext2->glClear(GL_COLOR_BUFFER_BIT);

        context2->SwapBuffers();
        surface2->PollEvents();
    }

    return 0;
}
