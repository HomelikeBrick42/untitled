#include "Core/Defines.hpp"

#if PLATFORM_WINDOWS

    #include "WindowsOpenGLContext.hpp"

HMODULE WindowsOpenGLContext::OpenGL                           = nullptr;
HGLRC(WINAPI* WindowsOpenGLContext::wglCreateContext)(HDC)     = nullptr;
BOOL(WINAPI* WindowsOpenGLContext::wglDeleteContext)(HGLRC)    = nullptr;
HGLRC(WINAPI* WindowsOpenGLContext::wglGetCurrentContext)()    = nullptr;
HDC(WINAPI* WindowsOpenGLContext::wglGetCurrentDC)()           = nullptr;
PROC(WINAPI* WindowsOpenGLContext::wglGetProcAddress)(LPCSTR)  = nullptr;
BOOL(WINAPI* WindowsOpenGLContext::wglMakeCurrent)(HDC, HGLRC) = nullptr;

WindowsOpenGLContext::WindowsOpenGLContext(const Ref<Surface>& surface)
    : DrawSurface(surface.As<WindowsSurface>()), OpenGLContext(nullptr) {
    if (WindowsOpenGLContext::OpenGL == nullptr) {
        WindowsOpenGLContext::OpenGL = LoadLibraryA("OpenGL32.dll");
    #define LOAD(name)               \
        WindowsOpenGLContext::name = \
            (decltype(WindowsOpenGLContext::name))(void*)::GetProcAddress(WindowsOpenGLContext::OpenGL, #name)
        LOAD(wglCreateContext);
        LOAD(wglDeleteContext);
        LOAD(wglGetCurrentContext);
        LOAD(wglGetCurrentDC);
        LOAD(wglGetProcAddress);
        LOAD(wglMakeCurrent);
    #undef LOAD
    }

    PIXELFORMATDESCRIPTOR pixelFormatDescriptor = {};
    pixelFormatDescriptor.nSize                 = sizeof(pixelFormatDescriptor);
    pixelFormatDescriptor.nVersion              = 1;
    pixelFormatDescriptor.dwFlags               = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pixelFormatDescriptor.iPixelType            = PFD_TYPE_RGBA;
    pixelFormatDescriptor.cColorBits            = 32;
    pixelFormatDescriptor.cDepthBits            = 24;
    pixelFormatDescriptor.cStencilBits          = 8;
    pixelFormatDescriptor.iLayerType            = PFD_MAIN_PLANE;

    int format = ChoosePixelFormat(this->DrawSurface->DeviceContext, &pixelFormatDescriptor);
    if (format == 0) {
        // TODO: Error
    }

    if (!SetPixelFormat(this->DrawSurface->DeviceContext, format, &pixelFormatDescriptor)) {
        // TODO: Error
    }

    this->OpenGLContext = wglCreateContext(this->DrawSurface->DeviceContext);

    wglMakeCurrent(this->DrawSurface->DeviceContext, this->OpenGLContext);

    #define LOAD(name) \
        this->name##Func = reinterpret_cast<decltype(this->name##Func)>(WindowsOpenGLContext::GetProcAddress(#name))

    LOAD(glGetError);
    LOAD(glClearColor);
    LOAD(glClear);
    LOAD(glFlush);
    LOAD(glViewport);
    LOAD(glDrawArrays);
    LOAD(glGenBuffers);
    LOAD(glDeleteBuffers);
    LOAD(glBindBuffer);
    LOAD(glBufferData);
    LOAD(glGenVertexArrays);
    LOAD(glDeleteVertexArrays);
    LOAD(glBindVertexArray);
    LOAD(glEnableVertexAttribArray);
    LOAD(glVertexAttribPointer);
    LOAD(glCreateShader);
    LOAD(glDeleteShader);
    LOAD(glShaderSource);
    LOAD(glCompileShader);
    LOAD(glGetShaderiv);
    LOAD(glCreateProgram);
    LOAD(glDeleteProgram);
    LOAD(glAttachShader);
    LOAD(glDetachShader);
    LOAD(glLinkProgram);
    LOAD(glGetProgramiv);
    LOAD(glUseProgram);
    LOAD(glGetUniformLocation);
    LOAD(glProgramUniform1f);
    LOAD(glProgramUniform2f);
    LOAD(glProgramUniform3f);
    LOAD(glProgramUniform4f);
    LOAD(glProgramUniform1i);
    LOAD(glProgramUniformMatrix3fv);
    LOAD(glProgramUniformMatrix4fv);

    #undef LOAD
}

WindowsOpenGLContext::~WindowsOpenGLContext() {
    if (this->OpenGLContext) {
        this->glFlush();
        wglDeleteContext(this->OpenGLContext);
    }
}

void WindowsOpenGLContext::Present() {
    ::SwapBuffers(this->DrawSurface->DeviceContext);
}

void WindowsOpenGLContext::ChangeContextIfNecessary() {
    if (wglGetCurrentContext() != this->OpenGLContext) {
        wglMakeCurrent(this->DrawSurface->DeviceContext, this->OpenGLContext);
    }
}

void* WindowsOpenGLContext::GetProcAddress(const char* name) {
    void* func = reinterpret_cast<void*>(wglGetProcAddress(name));
    if (func == reinterpret_cast<void*>(0) || func == reinterpret_cast<void*>(1) || func == reinterpret_cast<void*>(2) ||
        func == reinterpret_cast<void*>(3) || func == reinterpret_cast<void*>(-1)) {
        func = reinterpret_cast<void*>(::GetProcAddress(WindowsOpenGLContext::OpenGL, name));
    }
    return func;
}

#endif
