#pragma once

#include "Surface.hpp"

#include <Windows.h>

class WindowsSurface final: public Surface {
public:
    friend class WindowsOpenGLContext;
public:
    WindowsSurface(u32 width, u32 height, const char* title);
    WindowsSurface(WindowsSurface&) = delete;
    WindowsSurface(WindowsSurface&&) = delete;
    ~WindowsSurface() final;
public:
    void PollEvents() final;
    void SetCloseCallback(CloseCallbackFunc* callback, void* userData) final {
        this->CloseCallback = callback;
        this->CloseCallbackUserData = userData;
    }
    void SetResizeCallback(ResizeCallbackFunc* callback, void* userData) final {
        this->ResizeCallback = callback;
        this->ResizeCallbackUserData = userData;
    }
private:
    static LRESULT WINAPI StaticWindowMessageCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    LRESULT WindowMessageCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
    HINSTANCE Instance;
    HWND WindowHandle;
    HDC DeviceContext;
private:
    CloseCallbackFunc* CloseCallback;
    void* CloseCallbackUserData;
    ResizeCallbackFunc* ResizeCallback;
    void* ResizeCallbackUserData;
private:
    static u64 SurfaceCount;
};
