#include "Core/Defines.hpp"

#if PLATFORM_WINDOWS

    #include "WindowsSurface.hpp"
    #include "WindowsOpenGLContext.hpp"

    #include <cstdlib>

static constexpr const char* WindowClassName = "ReplaceThisWindowClassName";
static constexpr DWORD WindowStyle =
    WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_THICKFRAME | WS_VISIBLE;
static constexpr DWORD WindowStyleEx = WS_EX_APPWINDOW;

u64 WindowsSurface::SurfaceCount = 0;

WindowsSurface::WindowsSurface(u32 width, u32 height, const char* title)
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

    this->WindowHandle = CreateWindowExA(WindowStyleEx,
                                         WindowClassName,
                                         title,
                                         WindowStyle,
                                         CW_USEDEFAULT,
                                         CW_USEDEFAULT,
                                         windowRect.right - windowRect.left,
                                         windowRect.bottom - windowRect.top,
                                         nullptr,
                                         nullptr,
                                         this->Instance,
                                         this);

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
    auto surface = reinterpret_cast<WindowsSurface*>(GetWindowLongPtrA(hWnd, GWLP_USERDATA));
    if (surface != nullptr) {
        return surface->WindowMessageCallback(hWnd, message, wParam, lParam);
    } else {
        if (message == WM_CREATE) {
            auto createStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
            surface           = static_cast<WindowsSurface*>(createStruct->lpCreateParams);
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

        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYUP: {
            bool pressed = message == WM_KEYDOWN || message == WM_SYSKEYDOWN;
            KeyCode key  = KeyCode_Unknown;
            switch (wParam) {
    #define KEY(value, keycode) \
        case value: {           \
            key = keycode;      \
        } break;
                KEY(0x30, KeyCode_0);
                KEY(0x31, KeyCode_1);
                KEY(0x32, KeyCode_2);
                KEY(0x33, KeyCode_3);
                KEY(0x34, KeyCode_4);
                KEY(0x35, KeyCode_5);
                KEY(0x36, KeyCode_6);
                KEY(0x37, KeyCode_7);
                KEY(0x38, KeyCode_8);
                KEY(0x39, KeyCode_9);

                KEY(0x41, KeyCode_A);
                KEY(0x42, KeyCode_B);
                KEY(0x43, KeyCode_C);
                KEY(0x44, KeyCode_D);
                KEY(0x45, KeyCode_E);
                KEY(0x46, KeyCode_F);
                KEY(0x47, KeyCode_G);
                KEY(0x48, KeyCode_H);
                KEY(0x49, KeyCode_I);
                KEY(0x4A, KeyCode_J);
                KEY(0x4B, KeyCode_K);
                KEY(0x4C, KeyCode_L);
                KEY(0x4D, KeyCode_M);
                KEY(0x4E, KeyCode_N);
                KEY(0x4F, KeyCode_O);
                KEY(0x50, KeyCode_P);
                KEY(0x51, KeyCode_Q);
                KEY(0x52, KeyCode_R);
                KEY(0x53, KeyCode_S);
                KEY(0x54, KeyCode_T);
                KEY(0x55, KeyCode_U);
                KEY(0x56, KeyCode_V);
                KEY(0x57, KeyCode_W);
                KEY(0x58, KeyCode_X);
                KEY(0x59, KeyCode_Y);
                KEY(0x5A, KeyCode_Z);
    #undef KEY
                default: {
                    key = KeyCode_Unknown;
                } break;
            }

            for (u64 i = 0; i < (lParam & 0xFF); i++) {
                this->KeyCallback(this, this->KeyCallbackUserData, key, pressed);
            }

            result = DefWindowProcA(hWnd, message, wParam, lParam);
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
