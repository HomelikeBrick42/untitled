#include "OpenGLContext.hpp"
#include "Renderer/OpenGL/OpenGLVertexBuffer.hpp"
#include "Renderer/OpenGL/OpenGLShader.hpp"

Ref<VertexBuffer> OpenGLContext::CreateVertexBuffer(const void* data, u64 size, const std::vector<VertexBufferElement>& layout) {
    return Ref<OpenGLVertexBuffer>::Create(this, data, size, layout);
}

Ref<Shader> OpenGLContext::CreateShader(const String& vertexSource, const String& fragmentSource) {
    return Ref<OpenGLShader>::Create(this, vertexSource, fragmentSource);
}
