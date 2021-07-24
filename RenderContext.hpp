#pragma once

#include "Defines.hpp"
#include "Surface.hpp"
#include "Ref.hpp"

enum class RendererAPI {
    OpenGL,
};

class RenderContext: public IRef {
public:
    static Ref<RenderContext> Create(const Ref<Surface>& surface, RendererAPI api);
    RenderContext(RenderContext&) = delete;
    RenderContext(RenderContext&&) = delete;
    virtual ~RenderContext() = default;
public:
    virtual void Present() = 0;
protected:
    RenderContext() = default;
};
