#include "RenderContext.hpp"

#if PLATFORM_WINDOWS
    #include "WindowsOpenGLRenderContext.hpp"
#endif

Ref<RenderContext> RenderContext::Create(Surface *surface, RendererAPI api) {
    switch (api) {
        case RendererAPI::OpenGL:
        #if PLATFORM_WINDOWS
            return Ref<WindowsOpenGLRenderContext>::Create(surface);
        #else
            return nullptr;
        #endif

        default:
            return nullptr;
    }
}
