#pragma once

#include "Renderer/VertexBuffer.hpp"
#include "Renderer/OpenGL/OpenGLContext.hpp"

class OpenGLVertexBuffer final: public VertexBuffer {
public:
    OpenGLVertexBuffer(const Ref<OpenGLContext>& context, const void* data, u64 size, const std::vector<VertexBufferElement>& elements);
    OpenGLVertexBuffer(OpenGLVertexBuffer&) = delete;
    OpenGLVertexBuffer(OpenGLVertexBuffer&&) = delete;
    ~OpenGLVertexBuffer() override;
public:
    void Bind() final;
    void UnBind() final;
    void SetData(const void* data, u64 size) final;
    void SetLayout(const std::vector<VertexBufferElement>& elements) final;
private:
    Ref<OpenGLContext> Context = nullptr;
    GLuint VertexArrayID = 0;
    GLuint ID = 0;
};
