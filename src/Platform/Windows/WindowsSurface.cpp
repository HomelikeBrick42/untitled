#include "Core/Defines.hpp"

#if PLATFORM_WINDOWS

    #include "WindowsSurface.hpp"
    #include "WindowsOpenGLContext.hpp"

    #include <cstdlib>

static constexpr const char *WindowClassName = "ReplaceThisWindowClassName";
static constexpr DWORD WindowStyle =
    WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_THICKFRAME | WS_VISIBLE;
static constexpr DWORD WindowStyleEx = WS_EX_APPWINDOW;

u64 WindowsSurface::SurfaceCount = 0;

WindowsSurface::WindowsSurface(u32 width, u32 height, const char *title)
    : Instance(GetModuleHandleA(nullptr)), WindowHandle(nullptr), DeviceContext(nullptr) {
    if (WindowsSurface::SurfaceCount == 0) {
        WNDCLASSEXA windowClass   = {};
        windowClass.cbSize        = sizeof(windowClass);
        windowClass.style         = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
        windowClass.lpfnWndProc   = WindowsSurface::StaticWindowMessageCallback;
        windowClass.hInstance     = this->Instance;
        windowClass.hCursor       = LoadCursor(nullptr, IDC_ARROW);
        windowClass.lpszClassName = WindowClassName;

        if (RegisterClassExA(&windowClass) == 0) {
            // TODO: Proper errors
            MessageBox(nullptr, "Failed to register window class!", "Error", MB_ICONEXCLAMATION | MB_OK);
            std::exit(-1);
        }
    }
    WindowsSurface::SurfaceCount++;

    RECT windowRect   = {};
    windowRect.left   = 100;
    windowRect.right  = windowRect.left + width;
    windowRect.top    = 100;
    windowRect.bottom = windowRect.top + height;
    AdjustWindowRectEx(&windowRect, WindowStyle, false, WindowStyleEx);

    this->WindowHandle = CreateWindowExA(WindowStyleEx, WindowClassName, title, WindowStyle, CW_USEDEFAULT, CW_USEDEFAULT,
                                         windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, nullptr, nullptr,
                                         this->Instance, this);

    if (this->WindowHandle == nullptr) {
        // TODO: Proper errors
        MessageBox(nullptr, "Failed to create window!", "Error", MB_ICONEXCLAMATION | MB_OK);
        std::exit(-1);
    }

    this->DeviceContext = GetDC(this->WindowHandle);

    if (this->DeviceContext == nullptr) {
        // TODO: Proper errors
        MessageBox(nullptr, "Failed to get window device context!", "Error", MB_ICONEXCLAMATION | MB_OK);
        std::exit(-1);
    }
}

WindowsSurface::~WindowsSurface() {
    if (this->Instance != nullptr) {
        WindowsSurface::SurfaceCount--;

        if (this->WindowHandle != nullptr) {
            if (this->DeviceContext != nullptr) {
                ReleaseDC(this->WindowHandle, this->DeviceContext);
            }

            DestroyWindow(this->WindowHandle);
        }

        if (WindowsSurface::SurfaceCount == 0) {
            UnregisterClassA(WindowClassName, this->Instance);
        }
    }
}

void WindowsSurface::PollEvents() {
    MSG message = {};
    while (PeekMessageA(&message, this->WindowHandle, 0, 0, PM_REMOVE)) {
        TranslateMessage(&message);
        DispatchMessageA(&message);
    }
}

LRESULT WINAPI WindowsSurface::StaticWindowMessageCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    auto surface = reinterpret_cast<WindowsSurface *>(GetWindowLongPtrA(hWnd, GWLP_USERDATA));
    if (surface != nullptr) {
        return surface->WindowMessageCallback(hWnd, message, wParam, lParam);
    } else {
        if (message == WM_CREATE) {
            auto createStruct = reinterpret_cast<CREATESTRUCT *>(lParam);
            surface           = static_cast<WindowsSurface *>(createStruct->lpCreateParams);
            SetWindowLongPtrA(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(surface));
        }

        return DefWindowProcA(hWnd, message, wParam, lParam);
    }
}

LRESULT WindowsSurface::WindowMessageCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    LRESULT result = 0;

    switch (message) {
    case WM_CLOSE:
    case WM_QUIT:
    case WM_DESTROY: {
        this->CloseCallback(this, this->CloseCallbackUserData);
    } break;

    case WM_SIZE: {
        RECT clientRect = {};
        GetClientRect(this->WindowHandle, &clientRect);
        s32 width  = clientRect.right - clientRect.left;
        s32 height = clientRect.bottom - clientRect.top;
        if (width > 0 && height > 0) {
            this->ResizeCallback(this, this->ResizeCallbackUserData, static_cast<u32>(width), static_cast<u32>(height));
        }
    } break;

    default: {
        result = DefWindowProcA(hWnd, message, wParam, lParam);
    } break;
    }

    return result;
}

Ref<RenderContext> WindowsSurface::CreateRenderContext(RendererAPI api) {
    switch (api) {
    case RendererAPI::OpenGL:
        return Ref<WindowsOpenGLContext>::Create(this);

    default:
        return nullptr;
    }
    return nullptr;
}

#endif
