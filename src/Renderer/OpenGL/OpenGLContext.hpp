#pragma once

#include "Renderer/RenderContext.hpp"

using GLchar = char;
using GLboolean = bool;
using GLbyte = s8;
using GLubyte = u8;
using GLshort = s16;
using GLushort = u16;
using GLint = s32;
using GLuint = u32;
using GLfixed = s32;
using GLint64 = s64;
using GLuint64 = u64;
using GLsizei = u32;
using GLenum = u32;
using GLintptr = s64;
using GLsizeiptr = u64;
using GLsync = u64;
using GLbitfield = u32;
using GLfloat = f32;
using GLclampf = f32;
using GLdouble = f64;
using GLclampd = f64;

constexpr GLboolean GL_TRUE = true;
constexpr GLboolean GL_FALSE = false;

constexpr GLenum GL_COLOR_BUFFER_BIT = 16384;
constexpr GLenum GL_STENCIL_BUFFER_BIT = 1024;
constexpr GLenum GL_DEPTH_BUFFER_BIT = 256;

constexpr GLenum GL_ARRAY_BUFFER = 34962;
constexpr GLenum GL_ELEMENT_ARRAY_BUFFER = 34963;

constexpr GLenum GL_STATIC_DRAW = 35044;
constexpr GLenum GL_DYNAMIC_DRAW = 35048;

constexpr GLenum GL_TRIANGLE = 4;

constexpr GLenum GL_FLOAT = 5126;

class OpenGLContext: public RenderContext {
public:
    OpenGLContext(OpenGLContext&) = delete;
    OpenGLContext(OpenGLContext&&) = delete;
    ~OpenGLContext() override = default;
public:
    Ref<VertexBuffer> CreateVertexBuffer(const void* data, u64 size, const std::vector<VertexBufferElement>& elements) final;
public:
    virtual GLenum glGetError() = 0;
    virtual void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) = 0;
    virtual void glClear(GLenum mask) = 0;
    virtual void glFlush() = 0;
    virtual void glViewport(GLint x, GLint y, GLsizei width, GLsizei height) = 0;
    virtual void glDrawArrays(GLenum mode, GLint first, GLsizei count) = 0;
    virtual void glGenBuffers(GLsizei n, GLuint* buffers) = 0;
    virtual void glDeleteBuffers(GLsizei n, const GLuint* buffers) = 0;
    virtual void glBindBuffer(GLenum target, GLuint buffer) = 0;
    virtual void glBufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage) = 0;
    virtual void glGenVertexArrays(GLsizei n, GLuint* arrays) = 0;
    virtual void glDeleteVertexArrays(GLsizei n, const GLuint* arrays) = 0;
    virtual void glBindVertexArray(GLuint array) = 0;
    virtual void glEnableVertexAttribArray(GLuint index) = 0;
    virtual void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) = 0;
protected:
    OpenGLContext() = default;
};
