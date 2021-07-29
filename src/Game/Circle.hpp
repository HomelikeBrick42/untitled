#pragma once

#include "Core/Defines.hpp"
#include "Math/Vector2.hpp"

struct Circle {
    Vector2f Position;
    Vector2f Velocity;
    Vector2f Acceleration;
    f32 Radius;
    f32 Mass;
    f32 Bounce;
    f32 StaticFriction;
    f32 DynamicFriction;

    Circle(Vector2f position,
           f32 radius,
           f32 mass,
           Vector2f velocity   = 0.0f,
           f32 bounce          = 0.6f,
           f32 staticFriction  = 0.8f,
           f32 dynamicFriction = 0.8f)
        : Position(position)
        , Velocity(velocity)
        , Acceleration(0.0f)
        , Radius(radius)
        , Mass(mass)
        , Bounce(bounce)
        , StaticFriction(staticFriction)
        , DynamicFriction(dynamicFriction) {}
};
