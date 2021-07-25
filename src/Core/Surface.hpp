#pragma once

#include "Core/Defines.hpp"
#include "Core/Ref.hpp"
#include "Renderer/RenderContext.hpp"

#include <functional>

class Surface: public IRef {
public:
    using CloseCallbackFunc  = std::function<void(Surface *surface, void *userData)>;
    using ResizeCallbackFunc = std::function<void(Surface *surface, void *userData, u32 width, u32 height)>;
public:
    static Ref<Surface> Create(u32 width, u32 height, const char *title);
    Surface(Surface &)  = delete;
    Surface(Surface &&) = delete;
    virtual ~Surface()  = default;
public:
    virtual void PollEvents()                                                   = 0;
    virtual void SetCloseCallback(CloseCallbackFunc callback, void *userData)   = 0;
    virtual void SetResizeCallback(ResizeCallbackFunc callback, void *userData) = 0;
public:
    virtual Ref<RenderContext> CreateRenderContext(RendererAPI api) = 0;
protected:
    Surface() = default;
};
