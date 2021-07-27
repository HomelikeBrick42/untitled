#include "Core/Defines.hpp"
#include "Core/Surface.hpp"
#include "Renderer/RenderContext.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/VertexBuffer.hpp"

#include "Math/Matrix.hpp"

class Application {
public:
    Application()              = default;
    Application(Application&)  = delete;
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
        u32 width = 640;
        u32 height = 480;
        this->Surface = Surface::Create(width, height, "Surface");
        this->Surface->SetCloseCallback(BIND_MEMBER_FN(SurfaceCloseCallback), nullptr);
        this->Surface->SetResizeCallback(BIND_MEMBER_FN(SurfaceResizeCallback), nullptr);

        this->RenderContext = this->Surface->CreateRenderContext(RendererAPI::OpenGL);

        this->CircleShader = this->RenderContext->CreateShader(VertexShaderSource, FragmentShaderSource);

        f32 aspect = static_cast<f32>(width) / static_cast<f32>(height);
        this->CircleShader->SetMatrix4x4f("u_ProjectionMatrix", OrthographicProjection(-aspect, aspect, 1.0f, -1.0f, -1.0f, 1.0f));

        struct { Vector3f Position; Vector2f Coord; } vertices[] = {
            { { -0.5f, +0.5f, 0.0f }, { -1.0f, +1.0f } },
            { { +0.5f, +0.5f, 0.0f }, { +1.0f, +1.0f } },
            { { +0.5f, -0.5f, 0.0f }, { +1.0f, -1.0f } },
            { { -0.5f, +0.5f, 0.0f }, { -1.0f, +1.0f } },
            { { +0.5f, -0.5f, 0.0f }, { +1.0f, -1.0f } },
            { { -0.5f, -0.5f, 0.0f }, { -1.0f, -1.0f } },
        };
        this->TriangleVertexBuffer =
            this->RenderContext->CreateVertexBuffer(vertices, sizeof(vertices), { VertexBufferElement::Float3, VertexBufferElement::Float2 });
    }

    void Update() {
        this->Surface->PollEvents();
    }

    void Render() {
        this->RenderContext->SetClearColor({ 0.1f, 0.1f, 0.1f });
        this->RenderContext->Clear();

        this->CircleShader->Bind();
        this->CircleShader->SetMatrix4x4f("u_ViewMatrix", TranslationMatrix(Vector3f{ 0.0f, 0.0f, 0.0f }));
        this->CircleShader->SetMatrix4x4f("u_ModelMatrix", TranslationMatrix(Vector3f{ 0.0f, 0.0f, 0.0f }));
        this->CircleShader->SetVector4f("u_Color", { 1.0f, 0.0f, 0.0f, 1.0f });
        this->TriangleVertexBuffer->Bind();
        this->RenderContext->Draw(0, 6);

        this->RenderContext->Present();
    }

    void Shutdown() {}
private:
    void SurfaceCloseCallback(Surface* surface, void* userData) {
        this->Running = false;
    }

    void SurfaceResizeCallback(Surface* surface, void* userData, u32 width, u32 height) {
        this->RenderContext->SetViewport(0, 0, width, height);

        f32 aspect = static_cast<f32>(width) / static_cast<f32>(height);
        this->CircleShader->SetMatrix4x4f("u_ProjectionMatrix", OrthographicProjection(-aspect, aspect, 1.0f, -1.0f, -1.0f, 1.0f));
    }
private:
    bool Running = true;
private:
    Ref<Surface> Surface                   = nullptr;
    Ref<RenderContext> RenderContext       = nullptr;
    Ref<Shader> CircleShader               = nullptr;
    Ref<VertexBuffer> TriangleVertexBuffer = nullptr;
private:
    const String VertexShaderSource   = R"(
#version 440 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec2 a_Coord;

uniform mat4 u_ModelMatrix = mat4(1.0);
uniform mat4 u_ViewMatrix = mat4(1.0);
uniform mat4 u_ProjectionMatrix = mat4(1.0);

layout(location = 0) out vec2 v_Coord;

void main() {
    v_Coord = a_Coord;
    gl_Position = u_ModelMatrix * inverse(u_ViewMatrix) * u_ProjectionMatrix * a_Position;
}
)";
    const String FragmentShaderSource = R"(
#version 440 core

layout(location = 0) out vec4 o_Color;

layout(location = 0) in vec2 v_Coord;

uniform vec4 u_Color = vec4(1.0, 0.0, 1.0, 1.0);

void main() {
    if (length(v_Coord) > 1.0) {
        discard;
    }
    o_Color = u_Color;
}
)";
};

int main() {
    auto application = new Application();
    application->Run();
    delete application;
    return 0;
}
