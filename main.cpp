#include "Defines.hpp"
#include "Surface.hpp"
#include "OpenGLContext.hpp"

class Application {
public:
    Application() = default;
    Application(Application&) = delete;
    Application(Application&&) = delete;
public:
    void Run() {
        this->Init();
        while (this->Running) {
            this->Update();
            this->Render();
        }
        this->Shutdown();
    }
private:
    void Init() {
        this->Surface1 = Surface::Create(640, 480, "Surface 1");
        this->RenderContext1 = RenderContext::Create(this->Surface1, RendererAPI::OpenGL);
        this->OpenGLContext1 = this->RenderContext1.As<OpenGLContext>();

        this->Surface2 = Surface::Create(640, 480, "Surface 2");
        this->RenderContext2 = RenderContext::Create(this->Surface2, RendererAPI::OpenGL);
        this->OpenGLContext2 = this->RenderContext2.As<OpenGLContext>();

        this->Surface1->SetCloseCallback(BIND_FN(Application::SurfaceCloseCallback), nullptr);
        this->Surface2->SetCloseCallback(BIND_FN(Application::SurfaceCloseCallback), nullptr);

        this->Surface1->SetResizeCallback(BIND_FN(Application::SurfaceResizeCallback), this->OpenGLContext1.Raw());
        this->Surface2->SetResizeCallback(BIND_FN(Application::SurfaceResizeCallback), this->OpenGLContext2.Raw());
    }

    void Update() {
        this->Surface1->PollEvents();
        this->Surface2->PollEvents();
    }

    void Render() {
        this->OpenGLContext1->glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        this->OpenGLContext1->glClear(GL_COLOR_BUFFER_BIT);

        this->RenderContext1->Present();

        this->OpenGLContext2->glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        this->OpenGLContext2->glClear(GL_COLOR_BUFFER_BIT);

        this->RenderContext2->Present();
    }

    void Shutdown() {
    }
private:
    void SurfaceCloseCallback(Surface* surface, void* userData) {
        this->Running = false;
    }

    void SurfaceResizeCallback(Surface* surface, void* userData, u32 width, u32 height) {
        auto openglContext = static_cast<OpenGLContext*>(userData);
        openglContext->glViewport(0, 0, width, height);
    }
private:
    bool Running = true;
private:
    Ref<Surface> Surface1 = nullptr;
    Ref<RenderContext> RenderContext1 = nullptr;
    Ref<OpenGLContext> OpenGLContext1 = nullptr;
    Ref<Surface> Surface2 = nullptr;
    Ref<RenderContext> RenderContext2 = nullptr;
    Ref<OpenGLContext> OpenGLContext2 = nullptr;
};

int main() {
    auto application = new Application();
    application->Run();
    delete application;
    return 0;
}
