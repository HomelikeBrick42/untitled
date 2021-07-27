#pragma once

#include "Core/Defines.hpp"
#include "Math/Vector.hpp"

#include <cmath>

template<typename T>
using Vector4 = Vector<4, T>;

using Vector4f = Vector4<f32>;

template<typename T>
struct Matrix<4, 1, T> {
    union {
        struct {
            T x;
            T y;
            T z;
            T w;
        };
        struct {
            T r;
            T g;
            T b;
            T a;
        };
    };

    Matrix<4, 1, T>() : x(T()), y(T()), z(T()), w(T()) {}
    Matrix<4, 1, T>(const T& scalar) : x(scalar), y(scalar), z(scalar), w(scalar) {}
    Matrix<4, 1, T>(const T& x, const T& y, const T& z, const T& w) : x(x), y(y), z(z), w(w) {}

    T& operator[](u64 index) {
        switch (index) {
            case 0:
                return this->x;
            case 1:
                return this->y;
            case 2:
                return this->z;
            case 3:
                return this->w;
            default:
                // TODO: Error
                return this->x;
        }
    }

    const T& operator[](u64 index) const {
        switch (index) {
            case 0:
                return this->x;
            case 1:
                return this->y;
            case 2:
                return this->z;
            case 3:
                return this->w;
            default:
                // TODO: Error
                return this->x;
        }
    }

    static T Dot(const Vector4<T>& a, const Vector4<T>& b) {
        return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    }

    static Vector4<T> Normalise(const Vector4<T>& v) {
        T length = static_cast<T>(sqrt(static_cast<f64>(Vector4<T>::Dot(v, v))));
        if (length != T()) {
            return v / length;
        } else {
            return Vector4<T>();
        }
    }
};

template<typename T>
Vector4<T> operator+(const Vector4<T>& a, const Vector4<T>& b) {
    return {
        a.x + b.x,
        a.y + b.y,
        a.z + b.z,
        a.w + b.w,
    };
}

template<typename T>
Vector4<T>& operator+=(Vector4<T>& a, const Vector4<T>& b) {
    a = a + b;
    return a;
}

template<typename T>
Vector4<T> operator+(const Vector4<T>& a, const T& b) {
    return {
        a.x + b,
        a.y + b,
        a.z + b,
        a.w + b,
    };
}

template<typename T>
Vector4<T> operator+(const T& a, const Vector4<T>& b) {
    return {
        a + b.x,
        a + b.y,
        a + b.z,
        a + b.w,
    };
}

template<typename T>
Vector4<T> operator+=(Vector4<T>& a, const T& b) {
    a = a + b;
    return a;
}

template<typename T>
Vector4<T> operator-(const Vector4<T>& a, const Vector4<T>& b) {
    return {
        a.x - b.x,
        a.y - b.y,
        a.z - b.z,
        a.w - b.w,
    };
}

template<typename T>
Vector4<T>& operator-=(Vector4<T>& a, const Vector4<T>& b) {
    a = a - b;
    return a;
}

template<typename T>
Vector4<T> operator-(const Vector4<T>& a, const T& b) {
    return {
        a.x - b,
        a.y - b,
        a.z - b,
        a.w - b,
    };
}

template<typename T>
Vector4<T> operator-(const T& a, const Vector4<T>& b) {
    return {
        a - b.x,
        a - b.y,
        a - b.z,
        a - b.w,
    };
}

template<typename T>
Vector4<T> operator-=(Vector4<T>& a, const T& b) {
    a = a - b;
    return a;
}

template<typename T>
Vector4<T> operator*(const Vector4<T>& a, const Vector4<T>& b) {
    return {
        a.x * b.x,
        a.y * b.y,
        a.z * b.z,
        a.w * b.w,
    };
}

template<typename T>
Vector4<T>& operator*=(Vector4<T>& a, const Vector4<T>& b) {
    a = a * b;
    return a;
}

template<typename T>
Vector4<T> operator*(const Vector4<T>& a, const T& b) {
    return {
        a.x * b,
        a.y * b,
        a.z * b,
        a.w * b,
    };
}

template<typename T>
Vector4<T> operator*(const T& a, const Vector4<T>& b) {
    return {
        a * b.x,
        a * b.y,
        a * b.z,
        a * b.w,
    };
}

template<typename T>
Vector4<T> operator*=(Vector4<T>& a, const T& b) {
    a = a * b;
    return a;
}

template<typename T>
Vector4<T> operator/(const Vector4<T>& a, const Vector4<T>& b) {
    return {
        a.x / b.x,
        a.y / b.y,
        a.z / b.z,
        a.w / b.w,
    };
}

template<typename T>
Vector4<T>& operator/=(Vector4<T>& a, const Vector4<T>& b) {
    a = a / b;
    return a;
}

template<typename T>
Vector4<T> operator/(const Vector4<T>& a, const T& b) {
    return {
        a.x / b,
        a.y / b,
        a.z / b,
        a.w / b,
    };
}

template<typename T>
Vector4<T> operator/(const T& a, const Vector4<T>& b) {
    return {
        a / b.x,
        a / b.y,
        a / b.z,
        a / b.w,
    };
}

template<typename T>
Vector4<T> operator/=(Vector4<T>& a, const T& b) {
    a = a / b;
    return a;
}
