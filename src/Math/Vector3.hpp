#pragma once

#include "Core/Defines.hpp"
#include "Math/Vector.hpp"

#include <cmath>

template<typename T>
using Vector3 = Vector<3, T>;

using Vector3f = Vector3<f32>;

template<typename T>
struct Matrix<3, 1, T> {
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

    Matrix<3, 1, T>() : x(T()), y(T()), z(T()) {}

    Matrix<3, 1, T>(const T& scalar) : x(scalar), y(scalar), z(scalar) {}

    Matrix<3, 1, T>(const T& x, const T& y, const T& z) : x(x), y(y), z(z) {}

    T& operator[](u64 index) {
        switch (index) {
            case 0:
                return this->x;
            case 1:
                return this->y;
            case 2:
                return this->z;
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
            default:
                // TODO: Error
                return this->x;
        }
    }

    static T Dot(const Vector3<T>& a, const Vector3<T>& b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    static Vector3<T> Cross(const Vector3<T>& a, const Vector3<T>& b) {
        return {
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x,
        };
    }

    static Vector3<T> Normalise(const Vector3<T>& v) {
        T length = static_cast<T>(sqrt(static_cast<f64>(Vector3<T>::Dot(v, v))));
        if (length != T()) {
            return v / length;
        } else {
            return Vector3<T>();
        }
    }
};

template<typename T>
Vector3<T> operator+(const Vector3<T>& a, const Vector3<T>& b) {
    return {
        a.x + b.x,
        a.y + b.y,
        a.z + b.z,
    };
}

template<typename T>
Vector3<T>& operator+=(Vector3<T>& a, const Vector3<T>& b) {
    a = a + b;
    return a;
}

template<typename T>
Vector3<T> operator+(const Vector3<T>& a, const T& b) {
    return {
        a.x + b,
        a.y + b,
        a.z + b,
    };
}

template<typename T>
Vector3<T> operator+(const T& a, const Vector3<T>& b) {
    return {
        a + b.x,
        a + b.y,
        a + b.z,
    };
}

template<typename T>
Vector3<T> operator+=(Vector3<T>& a, const T& b) {
    a = a + b;
    return a;
}

template<typename T>
Vector3<T> operator-(const Vector3<T>& a, const Vector3<T>& b) {
    return {
        a.x - b.x,
        a.y - b.y,
        a.z - b.z,
    };
}

template<typename T>
Vector3<T>& operator-=(Vector3<T>& a, const Vector3<T>& b) {
    a = a - b;
    return a;
}

template<typename T>
Vector3<T> operator-(const Vector3<T>& a, const T& b) {
    return {
        a.x - b,
        a.y - b,
        a.z - b,
    };
}

template<typename T>
Vector3<T> operator-(const T& a, const Vector3<T>& b) {
    return {
        a - b.x,
        a - b.y,
        a - b.z,
    };
}

template<typename T>
Vector3<T> operator-=(Vector3<T>& a, const T& b) {
    a = a - b;
    return a;
}

template<typename T>
Vector3<T> operator*(const Vector3<T>& a, const Vector3<T>& b) {
    return {
        a.x * b.x,
        a.y * b.y,
        a.z * b.z,
    };
}

template<typename T>
Vector3<T>& operator*=(Vector3<T>& a, const Vector3<T>& b) {
    a = a * b;
    return a;
}

template<typename T>
Vector3<T> operator*(const Vector3<T>& a, const T& b) {
    return {
        a.x * b,
        a.y * b,
        a.z * b,
    };
}

template<typename T>
Vector3<T> operator*(const T& a, const Vector3<T>& b) {
    return {
        a * b.x,
        a * b.y,
        a * b.z,
    };
}

template<typename T>
Vector3<T> operator*=(Vector3<T>& a, const T& b) {
    a = a * b;
    return a;
}

template<typename T>
Vector3<T> operator/(const Vector3<T>& a, const Vector3<T>& b) {
    return {
        a.x / b.x,
        a.y / b.y,
        a.z / b.z,
    };
}

template<typename T>
Vector3<T>& operator/=(Vector3<T>& a, const Vector3<T>& b) {
    a = a / b;
    return a;
}

template<typename T>
Vector3<T> operator/(const Vector3<T>& a, const T& b) {
    return {
        a.x / b,
        a.y / b,
        a.z / b,
    };
}

template<typename T>
Vector3<T> operator/(const T& a, const Vector3<T>& b) {
    return {
        a / b.x,
        a / b.y,
        a / b.z,
    };
}

template<typename T>
Vector3<T> operator/=(Vector3<T>& a, const T& b) {
    a = a / b;
    return a;
}
