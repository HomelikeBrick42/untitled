#pragma once

#include "Core/Defines.hpp"
#include "Core/Ref.hpp"
#include "Containers/String.hpp"
#include "Math/Matrix.hpp"
#include "Math/Vector.hpp"
#include "Renderer/RenderContext.hpp"

class Shader: public IRef {
public:
    Shader(Shader&)   = delete;
    Shader(Shader&&)  = delete;
    virtual ~Shader() = default;
public:
    virtual void Bind() const   = 0;
    virtual void UnBind() const = 0;
public:
    virtual void SetInt(const char* name, s32 value)                       = 0;
    virtual void SetFloat(const char* name, f32 value)                     = 0;
    virtual void SetVector1f(const char* name, const Vector1f& vector)     = 0;
    virtual void SetVector2f(const char* name, const Vector2f& vector)     = 0;
    virtual void SetVector3f(const char* name, const Vector3f& vector)     = 0;
    virtual void SetVector4f(const char* name, const Vector4f& vector)     = 0;
    virtual void SetMatrix3x3f(const char* name, const Matrix3x3f& matrix) = 0;
    virtual void SetMatrix4x4f(const char* name, const Matrix4x4f& matrix) = 0;
public:
    virtual Ref<RenderContext> GetContext() const = 0;
protected:
    Shader() = default;
};
