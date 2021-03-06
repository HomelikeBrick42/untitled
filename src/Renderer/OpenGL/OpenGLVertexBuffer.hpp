#pragma once

#include "Renderer/VertexBuffer.hpp"
#include "Renderer/OpenGL/OpenGLContext.hpp"

class OpenGLVertexBuffer final: public VertexBuffer {
public:
    OpenGLVertexBuffer(const Ref<OpenGLContext>& context, const void* data, u64 size, const Array<VertexBufferElement>& elements);
    OpenGLVertexBuffer(OpenGLVertexBuffer&)  = delete;
    OpenGLVertexBuffer(OpenGLVertexBuffer&&) = delete;
    ~OpenGLVertexBuffer() override;
public:
    void Bind() const final;
    void UnBind() const final;
    void SetData(const void* data, u64 size) final;
    void SetLayout(const Array<VertexBufferElement>& layout) final;
public:
    Ref<RenderContext> GetContext() const final {
        return this->Context;
    }
private:
    mutable Ref<OpenGLContext> Context = nullptr;
    GLuint VertexArrayID               = 0;
    GLuint ID                          = 0;
};
