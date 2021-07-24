#include "RenderContext.hpp"

#if PLATFORM_WINDOWS
    #include "WindowsOpenGLContext.hpp"
#endif

Ref<RenderContext> RenderContext::Create(const Ref<Surface>& surface, RendererAPI api) {
    switch (api) {
        case RendererAPI::OpenGL:
        #if PLATFORM_WINDOWS
            return Ref<WindowsOpenGLContext>::Create(surface);
        #else
            return nullptr;
        #endif

        default:
            return nullptr;
    }
}
