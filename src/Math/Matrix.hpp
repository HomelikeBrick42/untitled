#pragma once

#include "Core/Defines.hpp"
#include "Math/Vector.hpp"

template<u64 R, u64 C, typename T>
struct Matrix {
    Vector<R, T> Cols[C] = {};

    Matrix<R, C, T>() = default;

    Vector<R, T>& operator[](u64 index) {
        // TODO: Error checking
        return this->Cols[index];
    }

    const Vector<R, T>& operator[](u64 index) const {
        // TODO: Error checking
        return this->Cols[index];
    }

    static Matrix<R, C, T> Identity() {
        Matrix<R, C, T> result;
        for (u64 i = 0; i < (R < C ? R : C); i++) {
            result[i][i] = T(1);
        }
        return result;
    }
};
