#pragma once

#include "Renderer/OpenGL/OpenGLContext.hpp"
#include "WindowsSurface.hpp"

class WindowsOpenGLContext final: public OpenGLContext {
public:
    WindowsOpenGLContext(const Ref<Surface>& surface);
    WindowsOpenGLContext(WindowsOpenGLContext&) = delete;
    WindowsOpenGLContext(WindowsOpenGLContext&&) = delete;
    ~WindowsOpenGLContext() final;
public:
    void Present() final;
public:
    GLenum glGetError() final {
        this->ChangeContextIfNecessary();
        return this->glGetErrorFunc();
    }
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
    void glDrawArrays(GLenum mode, GLint first, GLsizei count) final {
        this->ChangeContextIfNecessary();
        this->glDrawArraysFunc(mode, first, count);
    }
    void glGenBuffers(GLsizei n, GLuint* buffers) final {
        this->ChangeContextIfNecessary();
        this->glGenBuffersFunc(n, buffers);
    }
    void glDeleteBuffers(GLsizei n, const GLuint* buffers) final {
        this->ChangeContextIfNecessary();
        this->glDeleteBuffersFunc(n, buffers);
    }
    void glBindBuffer(GLenum target, GLuint buffer) final {
        this->ChangeContextIfNecessary();
        this->glBindBufferFunc(target, buffer);
    }
    void glBufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage) final {
        this->ChangeContextIfNecessary();
        this->glBufferDataFunc(target, size, data, usage);
    }
    void glGenVertexArrays(GLsizei n, GLuint* arrays) final {
        this->ChangeContextIfNecessary();
        this->glGenVertexArraysFunc(n, arrays);
    }
    void glDeleteVertexArrays(GLsizei n, const GLuint* arrays) final {
        this->ChangeContextIfNecessary();
        this->glDeleteVertexArraysFunc(n, arrays);
    }
    void glBindVertexArray(GLuint array) final {
        this->ChangeContextIfNecessary();
        this->glBindVertexArrayFunc(array);
    }
    void glEnableVertexAttribArray(GLuint index) final {
        this->ChangeContextIfNecessary();
        this->glEnableVertexAttribArrayFunc(index);
    }
    void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) final {
        this->ChangeContextIfNecessary();
        this->glVertexAttribPointerFunc(index, size, type, normalized, stride, pointer);
    }
private:
    GLenum (APIENTRY *glGetErrorFunc)() = nullptr;
    void (APIENTRY *glClearColorFunc)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) = nullptr;
    void (APIENTRY *glClearFunc)(GLenum mask) = nullptr;
    void (APIENTRY *glFlushFunc)() = nullptr;
    void (APIENTRY *glViewportFunc)(GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
    void (APIENTRY *glDrawArraysFunc)(GLenum mode, GLint first, GLsizei count) = nullptr;
    void (APIENTRY *glGenBuffersFunc)(GLsizei n, GLuint* buffer) = nullptr;
    void (APIENTRY *glDeleteBuffersFunc)(GLsizei n, const GLuint* buffers) = nullptr;
    void (APIENTRY *glBindBufferFunc)(GLenum target, GLuint buffer) = nullptr;
    void (APIENTRY *glBufferDataFunc)(GLenum target, GLsizeiptr size, const void* data, GLenum usage) = nullptr;
    void (APIENTRY *glGenVertexArraysFunc)(GLsizei n, GLuint* arrays) = nullptr;
    void (APIENTRY *glDeleteVertexArraysFunc)(GLsizei n, const GLuint* arrays) = nullptr;
    void (APIENTRY *glBindVertexArrayFunc)(GLuint array) = nullptr;
    void (APIENTRY *glEnableVertexAttribArrayFunc)(GLuint index) = nullptr;
    void (APIENTRY *glVertexAttribPointerFunc)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) = nullptr;
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
