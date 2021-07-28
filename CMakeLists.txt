cmake_minimum_required(VERSION 3.19)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" OR "x${CMAKE_CXX_SIMULATE_ID}" STREQUAL "xMSVC")
    add_compile_options(-W4)
else ()
    add_compile_options(
            -Wall
            -Wextra)
endif ()
add_compile_options(
        -Werror
        -Wno-unused-parameter)

add_compile_options(-D_USE_MATH_DEFINES)

include_directories(src)

add_executable(
        untitled
        src/Containers/Array.hpp
        src/Containers/String.cpp
        src/Containers/String.hpp
        src/Core/Defines.hpp
        src/Core/KeyCode.hpp
        src/Core/Ref.hpp
        src/Core/Surface.cpp
        src/Core/Surface.hpp
        src/Game/Circle.hpp
        src/Game/Main.cpp
        src/Math/Math.hpp
        src/Math/Matrix.hpp
        src/Math/Vector.hpp
        src/Math/Vector1.hpp
        src/Math/Vector2.hpp
        src/Math/Vector3.hpp
        src/Math/Vector4.hpp
        src/Platform/Windows/WindowsOpenGLContext.cpp
        src/Platform/Windows/WindowsOpenGLContext.hpp
        src/Platform/Windows/WindowsSurface.cpp
        src/Platform/Windows/WindowsSurface.hpp
        src/Renderer/OpenGL/OpenGLContext.cpp
        src/Renderer/OpenGL/OpenGLContext.hpp
        src/Renderer/OpenGL/OpenGLShader.cpp
        src/Renderer/OpenGL/OpenGLShader.hpp
        src/Renderer/OpenGL/OpenGLVertexBuffer.cpp
        src/Renderer/OpenGL/OpenGLVertexBuffer.hpp
        src/Renderer/RenderContext.hpp
        src/Renderer/Shader.hpp
        src/Renderer/VertexBuffer.hpp
        src/Renderer/VertexBufferElement.hpp)
