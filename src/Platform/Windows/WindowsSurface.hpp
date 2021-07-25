#pragma once

#include "Core/Surface.hpp"

#include <Windows.h>

class WindowsSurface final: public Surface {
public:
    friend class WindowsOpenGLContext;
public:
    WindowsSurface(u32 width, u32 height, const char* title);
    WindowsSurface(WindowsSurface&)  = delete;
    WindowsSurface(WindowsSurface&&) = delete;
    ~WindowsSurface() final;
public:
    void PollEvents() final;
    void SetCloseCallback(CloseCallbackFunc callback, void* userData) final {
        this->CloseCallback         = callback;
        this->CloseCallbackUserData = userData;
    }
    void SetResizeCallback(ResizeCallbackFunc callback, void* userData) final {
        this->ResizeCallback         = callback;
        this->ResizeCallbackUserData = userData;
    }
public:
    Ref<RenderContext> CreateRenderContext(RendererAPI api) final;
private:
    static LRESULT WINAPI StaticWindowMessageCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    LRESULT WindowMessageCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
    HINSTANCE Instance = nullptr;
    HWND WindowHandle  = nullptr;
    HDC DeviceContext  = nullptr;
private:
    CloseCallbackFunc CloseCallback   = nullptr;
    void* CloseCallbackUserData       = nullptr;
    ResizeCallbackFunc ResizeCallback = nullptr;
    void* ResizeCallbackUserData      = nullptr;
private:
    static u64 SurfaceCount;
};
