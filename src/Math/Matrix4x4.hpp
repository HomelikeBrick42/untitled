#pragma once

#include "Core/Defines.hpp"
#include "Math/Matrix.hpp"
#include "Math/Vector4.hpp"

template<typename T>
using Matrix4x4 = Matrix<4, 4, T>;

using Matrix4x4f = Matrix4x4<f32>;
