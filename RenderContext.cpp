#include "RenderContext.hpp"

#if PLATFORM_WINDOWS
    #include "WindowsOpenGLRenderContext.hpp"
#endif

std::unique_ptr<RenderContext> RenderContext::Create(Surface *surface, RendererAPI api) {
    switch (api) {
        case RendererAPI::OpenGL:
        #if PLATFORM_WINDOWS
            return std::make_unique<WindowsOpenGLRenderContext>(surface);
        #else
            return nullptr;
        #endif

        default:
            return nullptr;
    }
}
