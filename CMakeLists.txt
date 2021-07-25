cmake_minimum_required(VERSION 3.19)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled main.cpp Defines.hpp Surface.cpp Surface.hpp WindowsSurface.cpp WindowsSurface.hpp RenderContext.hpp OpenGLContext.hpp WindowsOpenGLContext.cpp WindowsOpenGLContext.hpp Ref.hpp)
