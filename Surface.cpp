#include "Surface.hpp"

#if PLATFORM_WINDOWS
    #include "WindowsSurface.hpp"
#endif

std::unique_ptr<Surface> Surface::Create(u32 width, u32 height, const char *title) {
#if PLATFORM_WINDOWS
    return std::make_unique<WindowsSurface>(width, height, title);
#else
    return nullptr;
#endif
}
