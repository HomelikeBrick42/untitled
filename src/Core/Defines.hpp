#pragma once

#define BIND_MEMBER_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

using u8  = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long long;

using s8  = signed char;
using s16 = signed short;
using s32 = signed int;
using s64 = signed long long;

using f32 = float;
using f64 = double;

#define SIZE_ASSERT(type, size) static_assert(sizeof(type) == size, "Expected sizeof " #type " to be " #size " bytes.")

SIZE_ASSERT(u8, 1);
SIZE_ASSERT(u16, 2);
SIZE_ASSERT(u32, 4);
SIZE_ASSERT(u64, 8);

SIZE_ASSERT(s8, 1);
SIZE_ASSERT(s16, 2);
SIZE_ASSERT(s32, 4);
SIZE_ASSERT(s64, 8);

SIZE_ASSERT(f32, 4);
SIZE_ASSERT(f64, 8);

#undef SIZE_ASSERT

#if defined(_WIN32)
    #if defined(_WIN64)
        #define PLATFORM_WINDOWS 1
    #else
        #error "x86 builds are not supported!"
    #endif
#else
    #error "Unknown platform!"
#endif

template<typename T>
char is_complete_(int (*)[sizeof(T)]);

template<typename>
char is_complete_(...);

template<typename T>
struct is_complete {
    enum { value = sizeof(is_complete_<T>(0)) != 1 };
};
