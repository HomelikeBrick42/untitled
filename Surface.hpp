#pragma once

#include "Defines.hpp"

#include <memory>

class Surface {
public:
    using CloseCallbackFunc = void(Surface* surface, void* userData);
    using ResizeCallbackFunc = void(Surface* surface, void* userData, u32 width, u32 height);
public:
    static std::unique_ptr<Surface> Create(u32 width, u32 height, const char* title);
    Surface(Surface&) = delete;
    Surface(Surface&&) = delete;
    virtual ~Surface() = default;
public:
    virtual void PollEvents() = 0;
    virtual void SetCloseCallback(CloseCallbackFunc* callback, void* userData) = 0;
    virtual void SetResizeCallback(ResizeCallbackFunc* callback, void* userData) = 0;
protected:
    Surface() = default;
};
