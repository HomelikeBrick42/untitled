#include "OpenGLShader.hpp"

OpenGLShader::OpenGLShader(const Ref<OpenGLContext>& context, const String& vertexSource, const String& fragmentSource)
    : Context(context) {
    GLuint vertexShader   = this->CreateShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragmentShader = this->CreateShader(GL_FRAGMENT_SHADER, fragmentSource);

    this->ID = this->Context->glCreateProgram();
    this->Context->glAttachShader(this->ID, vertexShader);
    this->Context->glAttachShader(this->ID, fragmentShader);
    this->Context->glLinkProgram(this->ID);

    GLint linked = GL_FALSE;
    this->Context->glGetProgramiv(this->ID, GL_LINK_STATUS, &linked);
    if (!linked) {
        // TODO: Error
    }

    this->Context->glDetachShader(this->ID, vertexShader);
    this->Context->glDeleteShader(vertexShader);

    this->Context->glDetachShader(this->ID, fragmentShader);
    this->Context->glDeleteShader(fragmentShader);
}

OpenGLShader::~OpenGLShader() {
    this->Context->glDeleteProgram(this->ID);
}

void OpenGLShader::Bind() const {
    this->Context->glUseProgram(this->ID);
}

void OpenGLShader::UnBind() const {
    this->Context->glUseProgram(0);
}

GLuint OpenGLShader::CreateShader(GLenum type, const String& source) {
    GLuint shader = this->Context->glCreateShader(type);
    GLint length  = (GLint)source.Length;
    this->Context->glShaderSource(shader, 1, (const GLchar**)&source.Data, (const GLint*)&length);
    this->Context->glCompileShader(shader);

    GLint compiled = GL_FALSE;
    this->Context->glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        // TODO: Error
    }

    return shader;
}
