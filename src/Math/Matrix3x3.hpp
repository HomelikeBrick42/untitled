#pragma once

#include "Core/Defines.hpp"
#include "Math/Math.hpp"
#include "Math/Matrix.hpp"

template<typename T>
using Matrix3x3 = Matrix<3, 3, T>;

using Matrix3x3f = Matrix3x3<f32>;
