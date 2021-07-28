#pragma once

#include "Core/Defines.hpp"
#include "Math/Vector2.hpp"

struct Circle {
    Vector2f Position;
    Vector2f Velocity;
    Vector2f Acceleration;
    f32 Mass;
    f32 Radius;

    Circle(Vector2f position, f32 radius, f32 mass, Vector2f velocity = 0.0f) : Position(position), Velocity(velocity), Acceleration(0.0f), Mass(mass), Radius(radius) {}
};
