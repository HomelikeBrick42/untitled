#pragma once

#include "Core/Defines.hpp"
#include "Math/Math.hpp"
#include "Math/Vector.hpp"

template<u64 R, u64 C, typename T>
struct Matrix {
    Vector<C, T> Rows[R] = {};

    Matrix<R, C, T>() = default;

    Vector<C, T>& operator[](u64 index) {
        // TODO: Error checking
        return this->Rows[index];
    }

    const Vector<C, T>& operator[](u64 index) const {
        // TODO: Error checking
        return this->Rows[index];
    }

    static Matrix<R, C, T> Identity() {
        Matrix<R, C, T> result;
        for (u64 i = 0; i < (R < C ? R : C); i++) {
            result[i][i] = T(1);
        }
        return result;
    }
};

template<u64 R1, u64 C1R2, u64 C2, typename T>
Matrix<R1, C2, T> operator*(const Matrix<R1, C1R2, T>& a, const Matrix<C1R2, C2, T>& b) {
    Matrix<R1, C2, T> result;
    for (u64 i = 0; i < R1; i++) {
        for (u64 j = 0; j < C2; j++) {
            T sum = T(0);
            for (u64 k = 0; k < C1R2; k++) {
                sum += a[i][k] * b[k][j];
            }
            result[i][j] = sum;
        }
    }
    return result;
}

template<u64 R, u64 Length, typename T>
Vector<Length, T> operator*(const Matrix<R, Length, T>& m, const Vector<Length, T>& v) {
    Matrix<Length, 1, T> b;
    for (u64 i = 0; i < Length; i++) {
        b[i][0] = v[i];
    }

    Matrix<Length, 1, T> matrixResult = m * b;

    Vector<Length, T> result;
    for (u64 i = 0; i < Length; i++) {
        result[i] = matrixResult[i][0];
    }
    return result;
}

template<u64 R, u64 Length, typename T>
Vector<Length, T> operator*(const Vector<Length, T>& v, const Matrix<R, Length, T>& m) {
    Matrix<Length, 1, T> b;
    for (u64 i = 0; i < Length; i++) {
        b[i][0] = v[i];
    }

    Matrix<Length, 1, T> matrixResult = b * m;

    Vector<Length, T> result;
    for (u64 i = 0; i < Length; i++) {
        result[i] = matrixResult[i][0];
    }
    return result;
}
