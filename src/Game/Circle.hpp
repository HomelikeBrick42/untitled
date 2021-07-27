#pragma once

#include "Core/Defines.hpp"
#include "Math/Vector2.hpp"

struct Circle {
    Vector2f Position;
    Vector2f Velocity;
    Vector2f Acceleration;
    f32 Radius;

    Circle(Vector2f position, f32 radius) : Position(position), Velocity(0.0f), Acceleration(0.0f), Radius(radius) {}
};
