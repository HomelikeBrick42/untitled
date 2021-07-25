#include "OpenGLContext.hpp"
#include "Renderer/OpenGL/OpenGLVertexBuffer.hpp"

Ref<VertexBuffer> OpenGLContext::CreateVertexBuffer(const void* data, u64 size, const std::vector<VertexBufferElement>& elements) {
    return Ref<OpenGLVertexBuffer>::Create(this, data, size, elements);
}
