#pragma once

#include "OpenGLRenderContext.hpp"
#include "WindowsSurface.hpp"

class WindowsOpenGLRenderContext final: public OpenGLRenderContext {
public:
    explicit WindowsOpenGLRenderContext(Surface* surface);
    WindowsOpenGLRenderContext(WindowsOpenGLRenderContext&) = delete;
    WindowsOpenGLRenderContext(WindowsOpenGLRenderContext&&) = delete;
    ~WindowsOpenGLRenderContext() final;
public:
    void SwapBuffers() final;
public:
    void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) final {
        this->ChangeContextIfNecessary();
        this->glClearColorFunc(red, green, blue, alpha);
    }
    void glClear(GLenum mask) final {
        this->ChangeContextIfNecessary();
        this->glClearFunc(mask);
    }
    void glFlush(void) final {
        this->ChangeContextIfNecessary();
        this->glFlushFunc();
    }
private:
    void (APIENTRY *glClearColorFunc)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) = nullptr;
    void (APIENTRY *glClearFunc)(GLenum mask) = nullptr;
    void (APIENTRY *glFlushFunc)(void) = nullptr;
private:
    static HGLRC (WINAPI *wglCreateContext)(HDC);
    static BOOL (WINAPI *wglDeleteContext)(HGLRC);
    static HGLRC (WINAPI *wglGetCurrentContext)(void);
    static HDC (WINAPI *wglGetCurrentDC)(void);
    static PROC (WINAPI *wglGetProcAddress)(LPCSTR);
    static BOOL (WINAPI *wglMakeCurrent)(HDC, HGLRC);
private:
    void ChangeContextIfNecessary();
    static void* GetProcAddress(const char* name);
private:
    WindowsSurface* DrawSurface;
    HGLRC OpenGLContext;
private:
    static HMODULE OpenGL;
};
