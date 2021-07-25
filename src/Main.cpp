#include "Core/Defines.hpp"
#include "Core/Surface.hpp"
#include "Renderer/OpenGL/OpenGLContext.hpp"

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
        this->Surface = Surface::Create(640, 480, "Surface");
        this->Surface->SetCloseCallback(BIND_MEMBER_FN(Application::SurfaceCloseCallback), nullptr);
        this->Surface->SetResizeCallback(BIND_MEMBER_FN(Application::SurfaceResizeCallback), nullptr);

        this->RenderContext = this->Surface->CreateRenderContext(RendererAPI::OpenGL);
        this->OpenGLRenderContext = this->RenderContext.As<OpenGLContext>();

        f32 vertices[] = {
                +0.0f, +0.5f, 0.0f,
                +0.5f, -0.5f, 0.0f,
                -0.5f, -0.5f, 0.0f,
        };
        this->TriangleVertexBuffer = this->RenderContext->CreateVertexBuffer(vertices, sizeof(vertices), {
            VertexBufferElement::Float3
        });
    }

    void Update() {
        this->Surface->PollEvents();
    }

    void Render() {
        this->OpenGLRenderContext->glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        this->OpenGLRenderContext->glClear(GL_COLOR_BUFFER_BIT);

        this->TriangleVertexBuffer->Bind();
        this->OpenGLRenderContext->glDrawArrays(GL_TRIANGLE, 0, 3);

        this->RenderContext->Present();
    }

    void Shutdown() {
    }
private:
    void SurfaceCloseCallback(Surface* surface, void* userData) {
        this->Running = false;
    }

    void SurfaceResizeCallback(Surface* surface, void* userData, u32 width, u32 height) {
        this->OpenGLRenderContext->glViewport(0, 0, width, height);
    }
private:
    bool Running = true;
private:
    Ref<Surface> Surface = nullptr;
    Ref<RenderContext> RenderContext = nullptr;
    Ref<VertexBuffer> TriangleVertexBuffer = nullptr;
    Ref<OpenGLContext> OpenGLRenderContext = nullptr;
};

int main() {
    auto application = new Application();
    application->Run();
    delete application;
    return 0;
}
