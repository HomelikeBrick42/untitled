#pragma once

#include "Renderer/OpenGL/OpenGLContext.hpp"
#include "WindowsSurface.hpp"

class WindowsOpenGLContext final: public OpenGLContext {
public:
    explicit WindowsOpenGLContext(const Ref<Surface>& surface);
    WindowsOpenGLContext(WindowsOpenGLContext&) = delete;
    WindowsOpenGLContext(WindowsOpenGLContext&&) = delete;
    ~WindowsOpenGLContext() final;
public:
    void Present() final;
public:
    void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) final {
        this->ChangeContextIfNecessary();
        this->glClearColorFunc(red, green, blue, alpha);
    }
    void glClear(GLenum mask) final {
        this->ChangeContextIfNecessary();
        this->glClearFunc(mask);
    }
    void glFlush() final {
        this->ChangeContextIfNecessary();
        this->glFlushFunc();
    }
    void glViewport(GLint x, GLint y, GLsizei width, GLsizei height) final {
        this->ChangeContextIfNecessary();
        this->glViewportFunc(x, y, width, height);
    }
private:
    void (APIENTRY *glClearColorFunc)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) = nullptr;
    void (APIENTRY *glClearFunc)(GLenum mask) = nullptr;
    void (APIENTRY *glFlushFunc)() = nullptr;
    void (APIENTRY *glViewportFunc)(GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
private:
    static HGLRC (WINAPI *wglCreateContext)(HDC);
    static BOOL (WINAPI *wglDeleteContext)(HGLRC);
    static HGLRC (WINAPI *wglGetCurrentContext)();
    static HDC (WINAPI *wglGetCurrentDC)();
    static PROC (WINAPI *wglGetProcAddress)(LPCSTR);
    static BOOL (WINAPI *wglMakeCurrent)(HDC, HGLRC);
private:
    void ChangeContextIfNecessary();
    static void* GetProcAddress(const char* name);
private:
    Ref<WindowsSurface> DrawSurface;
    HGLRC OpenGLContext;
private:
    static HMODULE OpenGL;
};
