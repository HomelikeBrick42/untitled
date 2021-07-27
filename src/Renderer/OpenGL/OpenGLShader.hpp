#pragma once

#include "Renderer/Shader.hpp"
#include "Renderer/OpenGL/OpenGLContext.hpp"

class OpenGLShader final: public Shader {
public:
    OpenGLShader(const Ref<OpenGLContext>& context, const String& vertexSource, const String& fragmentSource);
    OpenGLShader(Shader&)  = delete;
    OpenGLShader(Shader&&) = delete;
    ~OpenGLShader() final;
public:
    void Bind() const final;
    void UnBind() const final;
private:
    GLuint CreateShader(GLenum type, const String& source);
public:
    void SetInt(const char* name, s32 value) final;
    void SetFloat(const char* name, f32 value) final;
    void SetVector1f(const char* name, const Vector1f& vector) final;
    void SetVector2f(const char* name, const Vector2f& vector) final;
    void SetVector3f(const char* name, const Vector3f& vector) final;
    void SetVector4f(const char* name, const Vector4f& vector) final;
    void SetMatrix3x3f(const char* name, const Matrix3x3f& matrix) final;
    void SetMatrix4x4f(const char* name, const Matrix4x4f& matrix) final;
public:
    Ref<RenderContext> GetContext() const final {
        return this->Context;
    }
private:
    mutable Ref<OpenGLContext> Context = nullptr;
    GLuint ID                          = 0;
};
