#pragma once

#include "Core/Defines.hpp"
#include "Core/Ref.hpp"
#include "Renderer/RenderContext.hpp"
#include "Renderer/VertexBufferElement.hpp"
#include "Containers/Array.hpp"

class VertexBuffer: public IRef {
public:
    VertexBuffer(VertexBuffer&)  = delete;
    VertexBuffer(VertexBuffer&&) = delete;
    virtual ~VertexBuffer()      = default;
public:
    virtual void Bind() const                                        = 0;
    virtual void UnBind() const                                      = 0;
    virtual void SetData(const void* data, u64 size)                 = 0;
    virtual void SetLayout(const Array<VertexBufferElement>& layout) = 0;
public:
    virtual Ref<RenderContext> GetContext() const = 0;
protected:
    VertexBuffer() = default;
};
