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

        auto closeCallback = [](Surface* surface, void* userData) -> void {
            auto running = static_cast<bool*>(userData);
            *running = false;
        };

        this->Surface1->SetCloseCallback(closeCallback, &this->Running);
        this->Surface2->SetCloseCallback(closeCallback, &this->Running);

        auto resizeCallback = [](Surface* surface, void* userData, u32 width, u32 height) -> void {
            auto openglContext = static_cast<OpenGLContext*>(userData);
            openglContext->glViewport(0, 0, width, height);
        };

        this->Surface1->SetResizeCallback(resizeCallback, this->OpenGLContext1.Raw());
        this->Surface2->SetResizeCallback(resizeCallback, this->OpenGLContext2.Raw());
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
    bool Running = true;
private:
    Ref<Surface> Surface1;
    Ref<RenderContext> RenderContext1;
    Ref<OpenGLContext> OpenGLContext1;
    Ref<Surface> Surface2;
    Ref<RenderContext> RenderContext2;
    Ref<OpenGLContext> OpenGLContext2;
};

int main() {
    auto application = new Application();
    application->Run();
    delete application;
    return 0;
}
