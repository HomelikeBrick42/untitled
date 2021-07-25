#include "OpenGLVertexBuffer.hpp"

OpenGLVertexBuffer::OpenGLVertexBuffer(const Ref<OpenGLContext>& context,
                                       const void* data,
                                       u64 size,
                                       const std::vector<VertexBufferElement>& elements)
    : Context(context) {
    this->Context->glGenBuffers(1, &this->ID);
    this->Context->glGenVertexArrays(1, &this->VertexArrayID);
    this->SetData(data, size);
    this->SetLayout(elements);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer() {
    this->Context->glDeleteBuffers(1, &this->ID);
    this->Context->glDeleteVertexArrays(1, &this->VertexArrayID);
}

void OpenGLVertexBuffer::Bind() const {
    this->Context->glBindVertexArray(this->VertexArrayID);
    this->Context->glBindBuffer(GL_ARRAY_BUFFER, this->ID);
}

void OpenGLVertexBuffer::UnBind() const {
    this->Context->glBindVertexArray(0);
    this->Context->glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLVertexBuffer::SetData(const void* data, u64 size) {
    this->Bind();
    this->Context->glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    this->UnBind();
}

void OpenGLVertexBuffer::SetLayout(const std::vector<VertexBufferElement>& layout) {
    auto getElementSize = [](VertexBufferElement element) -> GLsizei {
        switch (element) {
        case VertexBufferElement::Float:
            return sizeof(GLfloat);
        case VertexBufferElement::Float2:
            return sizeof(GLfloat) * 2;
        case VertexBufferElement::Float3:
            return sizeof(GLfloat) * 3;
        case VertexBufferElement::Float4:
            return sizeof(GLfloat) * 4;
        default:
            return 0;
        }
        return 0;
    };

    auto getElementCount = [](VertexBufferElement element) -> GLint {
        switch (element) {
        case VertexBufferElement::Float:
            return 1;
        case VertexBufferElement::Float2:
            return 2;
        case VertexBufferElement::Float3:
            return 3;
        case VertexBufferElement::Float4:
            return 4;
        default:
            return 0;
        }
        return 0;
    };

    auto elementToOpenGLType = [](VertexBufferElement element) -> GLenum {
        switch (element) {
        case VertexBufferElement::Float:
        case VertexBufferElement::Float2:
        case VertexBufferElement::Float3:
        case VertexBufferElement::Float4:
            return GL_FLOAT;
        default:
            return 0;
        }
        return 0;
    };

    this->Bind();

    GLsizei stride = 0;
    for (const auto& element : layout) {
        stride += getElementSize(element);
    }

    GLsizei offset = 0;
    GLuint index   = 0;
    for (const auto& element : layout) {
        this->Context->glEnableVertexAttribArray(index);
        this->Context->glVertexAttribPointer(index,
                                             getElementCount(element),
                                             elementToOpenGLType(element),
                                             GL_FALSE,
                                             stride,
                                             reinterpret_cast<const void*>(offset));
        offset += getElementSize(element);
        index++;
    }

    this->UnBind();
}
