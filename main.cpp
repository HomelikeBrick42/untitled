#include "Defines.hpp"
#include "Surface.hpp"
#include "OpenGLRenderContext.hpp"

int main() {
    auto surface1 = Surface::Create(640, 480, "Window 1");
    auto context1 = RenderContext::Create(surface1, RendererAPI::OpenGL);
    auto openglContext1 = context1.As<OpenGLRenderContext>();

    auto surface2 = Surface::Create(640, 480, "Window 2");
    auto context2 = RenderContext::Create(surface2, RendererAPI::OpenGL);
    auto openglContext2 = context2.As<OpenGLRenderContext>();

    bool running = true;

    auto closeCallback = [](Surface* surface, void* userData) -> void {
        auto running = static_cast<bool*>(userData);
        *running = false;
    };

    surface1->SetCloseCallback(closeCallback, &running);
    surface2->SetCloseCallback(closeCallback, &running);

    auto resizeCallback = [](Surface* surface, void* userData, u32 width, u32 height) -> void {
        auto openglContext = static_cast<OpenGLRenderContext*>(userData);
        openglContext->glViewport(0, 0, width, height);
    };

    surface1->SetResizeCallback(resizeCallback, openglContext1.Raw());
    surface2->SetResizeCallback(resizeCallback, openglContext2.Raw());

    while (running) {
        openglContext1->glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        openglContext1->glClear(GL_COLOR_BUFFER_BIT);

        context1->Present();
        surface1->PollEvents();

        openglContext2->glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        openglContext2->glClear(GL_COLOR_BUFFER_BIT);

        context2->Present();
        surface2->PollEvents();
    }

    return 0;
}
