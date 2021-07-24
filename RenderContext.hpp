#pragma once

#include "Defines.hpp"
#include "Surface.hpp"

#include <memory>

enum class RendererAPI {
    OpenGL,
};

class RenderContext {
public:
    static std::unique_ptr<RenderContext> Create(Surface* surface, RendererAPI api);
    RenderContext(RenderContext&) = delete;
    RenderContext(RenderContext&&) = delete;
    virtual ~RenderContext() = default;
public:
    virtual void SwapBuffers() = 0;
protected:
    RenderContext() = default;
};
