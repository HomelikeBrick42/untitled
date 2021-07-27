#pragma once

#include "Renderer/OpenGL/OpenGLContext.hpp"
#include "WindowsSurface.hpp"

class WindowsOpenGLContext final: public OpenGLContext {
public:
    WindowsOpenGLContext(const Ref<Surface>& surface);
    WindowsOpenGLContext(WindowsOpenGLContext&)  = delete;
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
        return this->glClearColorFunc(red, green, blue, alpha);
    }
    void glClear(GLenum mask) final {
        this->ChangeContextIfNecessary();
        return this->glClearFunc(mask);
    }
    void glFlush() final {
        this->ChangeContextIfNecessary();
        return this->glFlushFunc();
    }
    void glViewport(GLint x, GLint y, GLsizei width, GLsizei height) final {
        this->ChangeContextIfNecessary();
        return this->glViewportFunc(x, y, width, height);
    }
    void glDrawArrays(GLenum mode, GLint first, GLsizei count) final {
        this->ChangeContextIfNecessary();
        return this->glDrawArraysFunc(mode, first, count);
    }
    void glGenBuffers(GLsizei n, GLuint* buffers) final {
        this->ChangeContextIfNecessary();
        return this->glGenBuffersFunc(n, buffers);
    }
    void glDeleteBuffers(GLsizei n, const GLuint* buffers) final {
        this->ChangeContextIfNecessary();
        return this->glDeleteBuffersFunc(n, buffers);
    }
    void glBindBuffer(GLenum target, GLuint buffer) final {
        this->ChangeContextIfNecessary();
        return this->glBindBufferFunc(target, buffer);
    }
    void glBufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage) final {
        this->ChangeContextIfNecessary();
        return this->glBufferDataFunc(target, size, data, usage);
    }
    void glGenVertexArrays(GLsizei n, GLuint* arrays) final {
        this->ChangeContextIfNecessary();
        return this->glGenVertexArraysFunc(n, arrays);
    }
    void glDeleteVertexArrays(GLsizei n, const GLuint* arrays) final {
        this->ChangeContextIfNecessary();
        return this->glDeleteVertexArraysFunc(n, arrays);
    }
    void glBindVertexArray(GLuint array) final {
        this->ChangeContextIfNecessary();
        return this->glBindVertexArrayFunc(array);
    }
    void glEnableVertexAttribArray(GLuint index) final {
        this->ChangeContextIfNecessary();
        return this->glEnableVertexAttribArrayFunc(index);
    }
    void glVertexAttribPointer(
        GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) final {
        this->ChangeContextIfNecessary();
        return this->glVertexAttribPointerFunc(index, size, type, normalized, stride, pointer);
    }
    GLuint glCreateShader(GLenum shaderType) final {
        this->ChangeContextIfNecessary();
        return this->glCreateShaderFunc(shaderType);
    }
    void glDeleteShader(GLuint shader) final {
        this->ChangeContextIfNecessary();
        return this->glDeleteShaderFunc(shader);
    }
    void glShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length) final {
        this->ChangeContextIfNecessary();
        return this->glShaderSourceFunc(shader, count, string, length);
    }
    void glCompileShader(GLuint shader) final {
        this->ChangeContextIfNecessary();
        return this->glCompileShaderFunc(shader);
    }
    void glGetShaderiv(GLuint shader, GLenum pname, GLint* params) final {
        this->ChangeContextIfNecessary();
        return this->glGetShaderivFunc(shader, pname, params);
    }
    GLuint glCreateProgram() final {
        this->ChangeContextIfNecessary();
        return this->glCreateProgramFunc();
    }
    void glDeleteProgram(GLuint program) final {
        this->ChangeContextIfNecessary();
        return this->glDeleteProgramFunc(program);
    }
    void glAttachShader(GLuint program, GLuint shader) final {
        this->ChangeContextIfNecessary();
        return this->glAttachShaderFunc(program, shader);
    }
    void glDetachShader(GLuint program, GLuint shader) final {
        this->ChangeContextIfNecessary();
        return this->glDetachShaderFunc(program, shader);
    }
    void glLinkProgram(GLuint program) final {
        this->ChangeContextIfNecessary();
        return this->glLinkProgramFunc(program);
    }
    void glGetProgramiv(GLuint program, GLenum pname, GLint* params) final {
        this->ChangeContextIfNecessary();
        return this->glGetProgramivFunc(program, pname, params);
    }
    void glUseProgram(GLuint program) final {
        this->ChangeContextIfNecessary();
        return this->glUseProgramFunc(program);
    }
    GLint glGetUniformLocation(GLuint program, const GLchar* name) final {
        this->ChangeContextIfNecessary();
        return this->glGetUniformLocationFunc(program, name);
    }
    void glProgramUniform1f(GLuint program, GLint location, GLfloat v0) final {
        this->ChangeContextIfNecessary();
        return this->glProgramUniform1fFunc(program, location, v0);
    }
    void glProgramUniform2f(GLuint program, GLint location, GLfloat v0, GLfloat v1) final {
        this->ChangeContextIfNecessary();
        return this->glProgramUniform2fFunc(program, location, v0, v1);
    }
    void glProgramUniform3f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2) final {
        this->ChangeContextIfNecessary();
        return this->glProgramUniform3fFunc(program, location, v0, v1, v2);
    }
    void glProgramUniform4f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) final {
        this->ChangeContextIfNecessary();
        return this->glProgramUniform4fFunc(program, location, v0, v1, v2, v3);
    }
    void glProgramUniform1i(GLuint program, GLint location, GLint v0) final {
        this->ChangeContextIfNecessary();
        return this->glProgramUniform1iFunc(program, location, v0);
    }
    void
    glProgramUniformMatrix3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) final {
        this->ChangeContextIfNecessary();
        return this->glProgramUniformMatrix3fvFunc(program, location, count, transpose, value);
    }
    void
    glProgramUniformMatrix4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) final {
        this->ChangeContextIfNecessary();
        return this->glProgramUniformMatrix4fvFunc(program, location, count, transpose, value);
    }
public:
    Ref<Surface> GetSurface() const final {
        return this->DrawSurface;
    }
private:
    GLenum(APIENTRY* glGetErrorFunc)()                                                               = nullptr;
    void(APIENTRY* glClearColorFunc)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)        = nullptr;
    void(APIENTRY* glClearFunc)(GLenum mask)                                                         = nullptr;
    void(APIENTRY* glFlushFunc)()                                                                    = nullptr;
    void(APIENTRY* glViewportFunc)(GLint x, GLint y, GLsizei width, GLsizei height)                  = nullptr;
    void(APIENTRY* glDrawArraysFunc)(GLenum mode, GLint first, GLsizei count)                        = nullptr;
    void(APIENTRY* glGenBuffersFunc)(GLsizei n, GLuint* buffer)                                      = nullptr;
    void(APIENTRY* glDeleteBuffersFunc)(GLsizei n, const GLuint* buffers)                            = nullptr;
    void(APIENTRY* glBindBufferFunc)(GLenum target, GLuint buffer)                                   = nullptr;
    void(APIENTRY* glBufferDataFunc)(GLenum target, GLsizeiptr size, const void* data, GLenum usage) = nullptr;
    void(APIENTRY* glGenVertexArraysFunc)(GLsizei n, GLuint* arrays)                                 = nullptr;
    void(APIENTRY* glDeleteVertexArraysFunc)(GLsizei n, const GLuint* arrays)                        = nullptr;
    void(APIENTRY* glBindVertexArrayFunc)(GLuint array)                                              = nullptr;
    void(APIENTRY* glEnableVertexAttribArrayFunc)(GLuint index)                                      = nullptr;
    void(APIENTRY* glVertexAttribPointerFunc)(
        GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)        = nullptr;
    GLuint(APIENTRY* glCreateShaderFunc)(GLenum shaderType)                                                      = nullptr;
    void(APIENTRY* glDeleteShaderFunc)(GLuint shader)                                                            = nullptr;
    void(APIENTRY* glShaderSourceFunc)(GLuint shader, GLsizei count, const GLchar** string, const GLint* length) = nullptr;
    void(APIENTRY* glCompileShaderFunc)(GLuint shader)                                                           = nullptr;
    void(APIENTRY* glGetShaderivFunc)(GLuint shader, GLenum pname, GLint* params)                                = nullptr;
    GLuint(APIENTRY* glCreateProgramFunc)()                                                                      = nullptr;
    void(APIENTRY* glDeleteProgramFunc)(GLuint program)                                                          = nullptr;
    void(APIENTRY* glAttachShaderFunc)(GLuint program, GLuint shader)                                            = nullptr;
    void(APIENTRY* glDetachShaderFunc)(GLuint program, GLuint shader)                                            = nullptr;
    void(APIENTRY* glLinkProgramFunc)(GLuint program)                                                            = nullptr;
    void(APIENTRY* glGetProgramivFunc)(GLuint program, GLenum pname, GLint* params)                              = nullptr;
    void(APIENTRY* glUseProgramFunc)(GLuint program)                                                             = nullptr;
    GLint(APIENTRY* glGetUniformLocationFunc)(GLuint program, const GLchar* name)                                = nullptr;
    void(APIENTRY* glProgramUniform1fFunc)(GLuint program, GLint location, GLfloat v0)                           = nullptr;
    void(APIENTRY* glProgramUniform2fFunc)(GLuint program, GLint location, GLfloat v0, GLfloat v1)               = nullptr;
    void(APIENTRY* glProgramUniform3fFunc)(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2)   = nullptr;
    void(APIENTRY* glProgramUniform4fFunc)(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) =
        nullptr;
    void(APIENTRY* glProgramUniform1iFunc)(GLuint program, GLint location, GLint v0) = nullptr;
    void(APIENTRY* glProgramUniformMatrix3fvFunc)(
        GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
    void(APIENTRY* glProgramUniformMatrix4fvFunc)(
        GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;
private:
    static HGLRC(WINAPI* wglCreateContext)(HDC);
    static BOOL(WINAPI* wglDeleteContext)(HGLRC);
    static HGLRC(WINAPI* wglGetCurrentContext)();
    static HDC(WINAPI* wglGetCurrentDC)();
    static PROC(WINAPI* wglGetProcAddress)(LPCSTR);
    static BOOL(WINAPI* wglMakeCurrent)(HDC, HGLRC);
private:
    void ChangeContextIfNecessary();
    static void* GetProcAddress(const char* name);
private:
    Ref<WindowsSurface> DrawSurface;
    HGLRC OpenGLContext;
private:
    static HMODULE OpenGL;
};
