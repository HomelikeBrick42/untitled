#pragma once

#include "Core/Defines.hpp"
#include "Core/Ref.hpp"
#include "Core/String.hpp"
#include "Renderer/VertexBufferElement.hpp"
#include "Math/Vector3.hpp"

#include <vector>

enum class RendererAPI {
    OpenGL,
};

class Shader;
class VertexBuffer;

class Surface;

class RenderContext: public IRef {
public:
    RenderContext(RenderContext &)  = delete;
    RenderContext(RenderContext &&) = delete;
    virtual ~RenderContext()        = default;
public:
    virtual Ref<Shader> CreateShader(const String &vertexSource, const String &fragmentSource)                               = 0;
    virtual Ref<VertexBuffer> CreateVertexBuffer(const void *data, u64 size, const std::vector<VertexBufferElement> &layout) = 0;
public:
    virtual void SetClearColor(const Vector3f &color)             = 0;
    virtual void Clear()                                          = 0;
    virtual void Draw(u32 first, u32 count)                       = 0;
    virtual void SetViewport(u32 x, u32 y, u32 width, u32 height) = 0;
    virtual void Present()                                        = 0;
public:
    virtual Ref<Surface> GetSurface() const = 0;
protected:
    RenderContext() = default;
};
