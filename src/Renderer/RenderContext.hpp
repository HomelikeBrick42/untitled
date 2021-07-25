#pragma once

#include "Core/Defines.hpp"
#include "Core/Ref.hpp"
#include "Renderer/VertexBuffer.hpp"
#include "Renderer/Shader.hpp"

enum class RendererAPI {
    OpenGL,
};

class RenderContext: public IRef {
public:
    RenderContext(RenderContext&) = delete;
    RenderContext(RenderContext&&) = delete;
    virtual ~RenderContext() = default;
public:
    virtual Ref<Shader> CreateShader(const String& vertexSource, const String& fragmentSource) = 0;
    virtual Ref<VertexBuffer> CreateVertexBuffer(const void* data, u64 size, const std::vector<VertexBufferElement>& layout) = 0;
public:
    virtual void Present() = 0;
protected:
    RenderContext() = default;
};
