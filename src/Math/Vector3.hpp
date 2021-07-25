#pragma once

#include "Core/Defines.hpp"

template<typename T>
struct Vector3 {
    union {
        struct {
            T x;
            T y;
            T z;
        };
        struct {
            T r;
            T g;
            T b;
        };
    };

    Vector3()
        : x(T()), y(T()), z(T()) {}

    Vector3(T scalar)
        : x(scalar), y(scalar), z(scalar) {}

    Vector3(T x, T y, T z)
        : x(x), y(y), z(y) {}
};

using Vector3f = Vector3<f32>;
