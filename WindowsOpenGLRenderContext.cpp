#include "Defines.hpp"

#if PLATFORM_WINDOWS

#include "WindowsOpenGLRenderContext.hpp"

HMODULE WindowsOpenGLRenderContext::OpenGL = nullptr;
HGLRC (WINAPI *WindowsOpenGLRenderContext::wglCreateContext)(HDC) = nullptr;
BOOL (WINAPI *WindowsOpenGLRenderContext::wglDeleteContext)(HGLRC) = nullptr;
HGLRC (WINAPI *WindowsOpenGLRenderContext::wglGetCurrentContext)(void) = nullptr;
HDC (WINAPI *WindowsOpenGLRenderContext::wglGetCurrentDC)(void) = nullptr;
PROC (WINAPI *WindowsOpenGLRenderContext::wglGetProcAddress)(LPCSTR) = nullptr;
BOOL (WINAPI *WindowsOpenGLRenderContext::wglMakeCurrent)(HDC, HGLRC) = nullptr;

WindowsOpenGLRenderContext::WindowsOpenGLRenderContext(Surface *surface)
    : DrawSurface(dynamic_cast<WindowsSurface*>(surface)), OpenGLContext(nullptr) {
    if (WindowsOpenGLRenderContext::OpenGL == nullptr) {
        WindowsOpenGLRenderContext::OpenGL = LoadLibraryA("OpenGL32.dll");
#define LOAD(name) WindowsOpenGLRenderContext::name = \
                    reinterpret_cast<decltype(WindowsOpenGLRenderContext::name)>( \
                        ::GetProcAddress(WindowsOpenGLRenderContext::OpenGL, #name))
        LOAD(wglCreateContext);
        LOAD(wglDeleteContext);
        LOAD(wglGetCurrentContext);
        LOAD(wglGetCurrentDC);
        LOAD(wglGetProcAddress);
        LOAD(wglMakeCurrent);
#undef LOAD
    }

    PIXELFORMATDESCRIPTOR pixelFormatDescriptor = {};
    pixelFormatDescriptor.nSize = sizeof(pixelFormatDescriptor);
    pixelFormatDescriptor.nVersion = 1;
    pixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
    pixelFormatDescriptor.cColorBits = 32;
    pixelFormatDescriptor.cDepthBits = 24;
    pixelFormatDescriptor.cStencilBits = 8;
    pixelFormatDescriptor.iLayerType = PFD_MAIN_PLANE;

    int format = ChoosePixelFormat(this->DrawSurface->DeviceContext, &pixelFormatDescriptor);
    if (format == 0) {
        // TODO: Error
    }

    if (!SetPixelFormat(this->DrawSurface->DeviceContext, format, &pixelFormatDescriptor)) {
        // TODO: Error
    }

    this->OpenGLContext = wglCreateContext(this->DrawSurface->DeviceContext);
    HGLRC prevContext = wglGetCurrentContext();
    HDC prevDeviceContext = wglGetCurrentDC();

    wglMakeCurrent(this->DrawSurface->DeviceContext, this->OpenGLContext);

#define LOAD(name) \
    this->name ## Func = reinterpret_cast<decltype(this->name ## Func)>(WindowsOpenGLRenderContext::GetProcAddress(#name))

    LOAD(glClearColor);
    LOAD(glClear);
    LOAD(glFlush);
    LOAD(glViewport);

#undef LOAD

    wglMakeCurrent(prevDeviceContext, prevContext);
}

WindowsOpenGLRenderContext::~WindowsOpenGLRenderContext() {
    if (this->OpenGLContext) {
        this->glFlush();
        wglDeleteContext(this->OpenGLContext);
    }
}

void WindowsOpenGLRenderContext::Present() {
    ::SwapBuffers(this->DrawSurface->DeviceContext);
}

void WindowsOpenGLRenderContext::ChangeContextIfNecessary() {
    if (wglGetCurrentContext() != this->OpenGLContext) {
        wglMakeCurrent(this->DrawSurface->DeviceContext, this->OpenGLContext);
    }
}

void* WindowsOpenGLRenderContext::GetProcAddress(const char* name) {
    void* func = reinterpret_cast<void*>(wglGetProcAddress(name));
    if (func == reinterpret_cast<void*>(0) ||
        func == reinterpret_cast<void*>(1) ||
        func == reinterpret_cast<void*>(2) ||
        func == reinterpret_cast<void*>(3) ||
        func == reinterpret_cast<void*>(-1)) {
        func = reinterpret_cast<void*>(::GetProcAddress(WindowsOpenGLRenderContext::OpenGL, name));
    }
    return func;
}

#endif
