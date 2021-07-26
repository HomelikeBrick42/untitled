#include "OpenGLContext.hpp"
#include "Renderer/OpenGL/OpenGLVertexBuffer.hpp"
#include "Renderer/OpenGL/OpenGLShader.hpp"

Ref<VertexBuffer> OpenGLContext::CreateVertexBuffer(const void* data, u64 size, const Array<VertexBufferElement>& layout) {
    return Ref<OpenGLVertexBuffer>::Create(this, data, size, layout);
}

Ref<Shader> OpenGLContext::CreateShader(const String& vertexSource, const String& fragmentSource) {
    return Ref<OpenGLShader>::Create(this, vertexSource, fragmentSource);
}

void OpenGLContext::SetClearColor(const Vector3f& color) {
    this->glClearColor(color.r, color.g, color.b, 1.0f);
}

void OpenGLContext::Clear() {
    this->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void OpenGLContext::Draw(u32 first, u32 count) {
    this->glDrawArrays(GL_TRIANGLES, (GLint)first, count);
}

void OpenGLContext::SetViewport(u32 x, u32 y, u32 width, u32 height) {
    this->glViewport((GLint)x, (GLint)y, width, height);
}
