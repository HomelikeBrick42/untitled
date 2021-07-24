#pragma once

#include "RenderContext.hpp"

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

class OpenGLRenderContext: public RenderContext {
public:
    OpenGLRenderContext(OpenGLRenderContext&) = delete;
    OpenGLRenderContext(OpenGLRenderContext&&) = delete;
    ~OpenGLRenderContext() override = default;
public:
    virtual void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) = 0;
    virtual void glClear(GLenum mask) = 0;
    virtual void glFlush(void) = 0;
protected:
    OpenGLRenderContext() = default;
};
