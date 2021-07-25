#pragma once

#include "Core/Defines.hpp"
#include "Core/Ref.hpp"
#include "Core/String.hpp"
#include "Renderer/RenderContext.hpp"

class Shader: public IRef {
public:
    Shader(Shader &)  = delete;
    Shader(Shader &&) = delete;
    virtual ~Shader() = default;

public:
    virtual void Bind() const   = 0;
    virtual void UnBind() const = 0;

public:
    virtual Ref<RenderContext> GetContext() const = 0;

protected:
    Shader() = default;
};
