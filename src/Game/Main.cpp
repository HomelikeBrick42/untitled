#include "Core/Defines.hpp"
#include "Core/Surface.hpp"
#include "Renderer/RenderContext.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/VertexBuffer.hpp"

#include "Math/Matrix.hpp"

#include "Game/Circle.hpp"

#include <chrono>

class Application {
public:
    Application()              = default;
    Application(Application&)  = delete;
    Application(Application&&) = delete;
public:
    void Run() {
        this->Init();
        using namespace std::chrono_literals;

        auto lastTime = std::chrono::high_resolution_clock::now();
        while (this->Running) {
            auto time = std::chrono::high_resolution_clock::now();
            f32 delta = std::chrono::duration<f32>(time - lastTime).count();
            lastTime  = std::chrono::high_resolution_clock::now();

            this->Update(delta);
            this->Render();
        }
        this->Shutdown();
    }
private:
    void Init() {
        u32 width     = 640;
        u32 height    = 480;
        this->Surface = Surface::Create(width, height, "Surface");
        this->Surface->SetCloseCallback(BIND_MEMBER_FN(SurfaceCloseCallback), nullptr);
        this->Surface->SetResizeCallback(BIND_MEMBER_FN(SurfaceResizeCallback), nullptr);

        this->RenderContext = this->Surface->CreateRenderContext(RendererAPI::OpenGL);

        this->CircleShader = this->RenderContext->CreateShader(VertexShaderSource, FragmentShaderSource);

        f32 aspect = static_cast<f32>(width) / static_cast<f32>(height);
        this->CircleShader->SetMatrix4x4f(
            "u_ProjectionMatrix",
            OrthographicProjection(-aspect * CameraZoom, aspect * CameraZoom, CameraZoom, -CameraZoom, -1.0f, 1.0f));

        struct {
            Vector3f Position;
            Vector2f Coord;
        } vertices[] = {
            { { -1.0f, +1.0f, 0.0f }, { -1.0f, +1.0f } }, { { +1.0f, +1.0f, 0.0f }, { +1.0f, +1.0f } },
            { { +1.0f, -1.0f, 0.0f }, { +1.0f, -1.0f } }, { { -1.0f, +1.0f, 0.0f }, { -1.0f, +1.0f } },
            { { +1.0f, -1.0f, 0.0f }, { +1.0f, -1.0f } }, { { -1.0f, -1.0f, 0.0f }, { -1.0f, -1.0f } },
        };
        this->TriangleVertexBuffer = this->RenderContext->CreateVertexBuffer(
            vertices, sizeof(vertices), { VertexBufferElement::Float3, VertexBufferElement::Float2 });

        this->Circles.Emplace(Vector2f{ -3.0f, 0.0f }, 1.0f, 1.0f, Vector2f{ +0.7f, 0.0f });
        this->Circles.Emplace(Vector2f{ +3.0f, 0.0f }, 1.0f, 2.0f, Vector2f{ -0.7f, 0.1f });
    }

    void Update(f32 dt) {
        for (u64 aIndex = 0; aIndex < this->Circles.Length; aIndex++) {
            Circle& circleA = Circles[aIndex];

            for (u64 bIndex = aIndex + 1; bIndex < this->Circles.Length; bIndex++) {
                Circle& circleB = Circles[bIndex];

                if (Vector2f::Length(circleB.Position - circleA.Position) < (circleA.Radius + circleB.Radius)) { // TODO: Optimise
                    Vector2f collisionNormal  = Vector2f::Normalise(circleB.Position - circleA.Position);
                    Vector2f relativeVelocity = circleB.Velocity - circleA.Velocity;
                    f32 normalSpeed           = Vector2f::Dot(relativeVelocity, collisionNormal);

                    f32 inverseMassA = 1.0f / circleA.Mass;
                    f32 inverseMassB = 1.0f / circleB.Mass;

                    if (normalSpeed >= 0.0f) { // Already moving away
                        continue;
                    }

                    // Impulse

                    f32 e            = 1.0f; // TODO: circleA.Bounce * circleB.Bounce
                    f32 j            = -(1.0f + e) * normalSpeed / (inverseMassA + inverseMassB);
                    Vector2f impulse = j * collisionNormal;

                    circleA.Velocity -= impulse * inverseMassA;
                    circleB.Velocity += impulse * inverseMassB;

                    // Friction

                    relativeVelocity = circleB.Velocity - circleA.Velocity;
                    normalSpeed      = Vector2f::Dot(relativeVelocity, collisionNormal);

                    Vector2f tangent = Vector2f::Normalise(relativeVelocity - normalSpeed * collisionNormal);

                    f32 fVelocity = Vector2f::Dot(relativeVelocity, tangent);

                    f32 aSF = 0.8f; // circleA.StaticFriction
                    f32 bSF = 0.8f; // circleB.StaticFriction
                    f32 aDF = 0.8f; // circleA.DynamicFriction
                    f32 bDF = 0.8f; // circleB.DynamicFriction
                    f32 mu  = Vector2f::Length({ aSF, bSF });

                    f32 f = -fVelocity / (inverseMassA + inverseMassB);

                    Vector2f friction;
                    if (fabsf(f) < j * mu) {
                        friction = f * tangent;
                    } else {
                        mu       = Vector2f::Length({ aDF, bDF });
                        friction = -j * tangent * mu;
                    }

                    circleA.Velocity -= friction * inverseMassA;
                    circleB.Velocity += friction * inverseMassB;
                }
            }

            circleA.Velocity += circleA.Acceleration / circleA.Mass * dt;
            circleA.Acceleration = 0.0;
            circleA.Position += circleA.Velocity * dt;
        }

        this->Surface->PollEvents();
    }

    void Render() {
        this->RenderContext->SetClearColor({ 0.1f, 0.1f, 0.1f });
        this->RenderContext->Clear();

        this->CircleShader->SetMatrix4x4f("u_ViewMatrix", Matrix4x4f::Identity());

        for (u64 i = 0; i < this->Circles.Length; i++) {
            Circle& circle = Circles[i];

            this->CircleShader->Bind();
            this->CircleShader->SetMatrix4x4f("u_ModelMatrix",
                                              ScaleMatrix(Vector3f{ circle.Radius }) *
                                                  TranslationMatrix(Vector3f{ circle.Position.x, circle.Position.y, 0.0f }));
            this->CircleShader->SetVector4f("u_Color", { 1.0f, 0.0f, 0.0f, 1.0f }); // TODO: Color per circle
            this->TriangleVertexBuffer->Bind();
            this->RenderContext->Draw(0, 6);
        }

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
        this->CircleShader->SetMatrix4x4f(
            "u_ProjectionMatrix",
            OrthographicProjection(-aspect * CameraZoom, aspect * CameraZoom, CameraZoom, -CameraZoom, -1.0f, 1.0f));
    }
private:
    bool Running = true;
private:
    f32 CameraZoom                         = 3.0f;
    Ref<Surface> Surface                   = nullptr;
    Ref<RenderContext> RenderContext       = nullptr;
    Ref<Shader> CircleShader               = nullptr;
    Ref<VertexBuffer> TriangleVertexBuffer = nullptr;
    Array<Circle> Circles                  = {};
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
    gl_Position = u_ProjectionMatrix * inverse(u_ViewMatrix) * u_ModelMatrix * a_Position;
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
