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

void OpenGLShader::SetInt(const char* name, s32 value) {
    GLint location = this->Context->glGetUniformLocation(this->ID, name);
    this->Context->glProgramUniform1i(this->ID, location, value);
}

void OpenGLShader::SetFloat(const char* name, f32 value) {
    GLint location = this->Context->glGetUniformLocation(this->ID, name);
    this->Context->glProgramUniform1f(this->ID, location, value);
}

void OpenGLShader::SetVector1f(const char* name, const Vector1f& vector) {
    GLint location = this->Context->glGetUniformLocation(this->ID, name);
    this->Context->glProgramUniform1f(this->ID, location, vector.x);
}

void OpenGLShader::SetVector2f(const char* name, const Vector2f& vector) {
    GLint location = this->Context->glGetUniformLocation(this->ID, name);
    this->Context->glProgramUniform2f(this->ID, location, vector.x, vector.y);
}

void OpenGLShader::SetVector3f(const char* name, const Vector3f& vector) {
    GLint location = this->Context->glGetUniformLocation(this->ID, name);
    this->Context->glProgramUniform3f(this->ID, location, vector.x, vector.y, vector.z);
}

void OpenGLShader::SetVector4f(const char* name, const Vector4f& vector) {
    GLint location = this->Context->glGetUniformLocation(this->ID, name);
    this->Context->glProgramUniform4f(this->ID, location, vector.x, vector.y, vector.z, vector.w);
}

void OpenGLShader::SetMatrix3x3f(const char* name, const Matrix3x3f& matrix) {
    GLint location = this->Context->glGetUniformLocation(this->ID, name);
    this->Context->glProgramUniformMatrix3fv(this->ID, location, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(&matrix));
}

void OpenGLShader::SetMatrix4x4f(const char* name, const Matrix4x4f& matrix) {
    GLint location = this->Context->glGetUniformLocation(this->ID, name);
    this->Context->glProgramUniformMatrix4fv(this->ID, location, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(&matrix));
}
