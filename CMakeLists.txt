cmake_minimum_required(VERSION 3.19)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wall -Wextra -Werror -Wno-unused-parameter)

include_directories(src)
add_executable(untitled src/Main.cpp src/Core/Defines.hpp src/Core/Surface.cpp src/Core/Surface.hpp src/Platform/Windows/WindowsSurface.cpp src/Platform/Windows/WindowsSurface.hpp src/Renderer/RenderContext.hpp src/Renderer/OpenGL/OpenGLContext.hpp src/Platform/Windows/WindowsOpenGLContext.cpp src/Platform/Windows/WindowsOpenGLContext.hpp src/Core/Ref.hpp src/Renderer/VertexBuffer.hpp src/Renderer/OpenGL/OpenGLVertexBuffer.cpp src/Renderer/OpenGL/OpenGLVertexBuffer.hpp src/Renderer/OpenGL/OpenGLContext.cpp src/Renderer/Shader.hpp src/Renderer/OpenGL/OpenGLShader.cpp src/Renderer/OpenGL/OpenGLShader.hpp src/Core/String.hpp src/Core/String.cpp src/Renderer/VertexBufferElement.hpp)
