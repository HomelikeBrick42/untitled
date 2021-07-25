#pragma once

#include "Renderer/Shader.hpp"
#include "Renderer/OpenGL/OpenGLContext.hpp"

class OpenGLShader final: public Shader {
public:
    OpenGLShader(const Ref<OpenGLContext>& context, const String& vertexSource, const String& fragmentSource);
    OpenGLShader(Shader&) = delete;
    OpenGLShader(Shader&&) = delete;
    ~OpenGLShader() final;
public:
    void Bind() const final;
    void UnBind() const final;
private:
    GLuint CreateShader(GLenum type, const String& source);
public:
    Ref<RenderContext> GetContext() const final { return this->Context; }
private:
    mutable Ref<OpenGLContext> Context = nullptr;
    GLuint ID = 0;
};
