#pragma once

#include "Core/Defines.hpp"
#include "Core/Ref.hpp"

#include <vector>

enum class VertexBufferElement {
    Float,
    Float2,
    Float3,
    Float4,
};

class VertexBuffer: public IRef {
public:
    VertexBuffer(VertexBuffer&) = delete;
    VertexBuffer(VertexBuffer&&) = delete;
    virtual ~VertexBuffer() = default;
public:
    virtual void Bind() const = 0;
    virtual void UnBind() const = 0;
    virtual void SetData(const void* data, u64 size) = 0;
    virtual void SetLayout(const std::vector<VertexBufferElement>& layout) = 0;
protected:
    VertexBuffer() = default;
};
