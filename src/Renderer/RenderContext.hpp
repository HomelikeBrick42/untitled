#pragma once

#include "Core/Defines.hpp"
#include "Core/Ref.hpp"
#include "Renderer/VertexBuffer.hpp"

enum class RendererAPI {
    OpenGL,
};

class RenderContext: public IRef {
public:
    RenderContext(RenderContext&) = delete;
    RenderContext(RenderContext&&) = delete;
    virtual ~RenderContext() = default;
public:
    virtual Ref<VertexBuffer> CreateVertexBuffer(const void* data, u64 size, const std::vector<VertexBufferElement>& elements) = 0;
public:
    virtual void Present() = 0;
protected:
    RenderContext() = default;
};
