#include "Surface.hpp"

#if PLATFORM_WINDOWS
    #include "WindowsSurface.hpp"
#endif

Ref<Surface> Surface::Create(u32 width, u32 height, const char *title) {
#if PLATFORM_WINDOWS
    return Ref<WindowsSurface>::Create(width, height, title);
#else
    return nullptr;
#endif
}
