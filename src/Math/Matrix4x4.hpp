#pragma once

#include "Core/Defines.hpp"
#include "Math/Math.hpp"
#include "Math/Matrix.hpp"

template<typename T>
using Matrix4x4 = Matrix<4, 4, T>;

using Matrix4x4f = Matrix4x4<f32>;
