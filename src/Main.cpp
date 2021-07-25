#include "Core/Defines.hpp"
#include "Core/Surface.hpp"
#include "Renderer/RenderContext.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/VertexBuffer.hpp"

class Application {
public:
    Application()               = default;
    Application(Application &)  = delete;
    Application(Application &&) = delete;
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
        this->Surface->SetCloseCallback(BIND_MEMBER_FN(SurfaceCloseCallback), nullptr);
        this->Surface->SetResizeCallback(BIND_MEMBER_FN(SurfaceResizeCallback), nullptr);

        this->RenderContext = this->Surface->CreateRenderContext(RendererAPI::OpenGL);

        this->ColorShader = this->RenderContext->CreateShader(VertexShaderSource, FragmentShaderSource);

        f32 vertices[] = {
            +0.0f, +0.5f, 0.0f, +0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f,
        };
        this->TriangleVertexBuffer =
            this->RenderContext->CreateVertexBuffer(vertices, sizeof(vertices), { VertexBufferElement::Float3 });
    }

    void Update() {
        this->Surface->PollEvents();
    }

    void Render() {
        this->RenderContext->SetClearColor({ 0.1f, 0.1f, 0.1f });
        this->RenderContext->Clear();

        this->ColorShader->Bind();
        this->TriangleVertexBuffer->Bind();
        this->RenderContext->Draw(0, 3);

        this->RenderContext->Present();
    }

    void Shutdown() {}
private:
    void SurfaceCloseCallback(Surface *surface, void *userData) {
        this->Running = false;
    }

    void SurfaceResizeCallback(Surface *surface, void *userData, u32 width, u32 height) {
        this->RenderContext->SetViewport(0, 0, width, height);
    }
private:
    bool Running = true;
private:
    Ref<Surface> Surface                   = nullptr;
    Ref<RenderContext> RenderContext       = nullptr;
    Ref<Shader> ColorShader                = nullptr;
    Ref<VertexBuffer> TriangleVertexBuffer = nullptr;
private:
    const String VertexShaderSource   = R"(
#version 440 core

layout(location = 0) in vec4 a_Position;

void main() {
    gl_Position = a_Position;
}
)";
    const String FragmentShaderSource = R"(
#version 440 core

layout(location = 0) out vec4 o_Color;

void main() {
    o_Color = vec4(1.0, 0.0, 0.0, 1.0);
}
)";
};

int main() {
    auto application = new Application();
    application->Run();
    delete application;
    return 0;
}
