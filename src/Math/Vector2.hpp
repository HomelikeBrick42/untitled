#pragma once

#include "Core/Defines.hpp"
#include "Math/Vector.hpp"

#include <cmath>

template<typename T>
using Vector2 = Vector<2, T>;

using Vector2f = Vector2<f32>;

template<typename T>
struct Matrix<2, 1, T> {
    union {
        struct {
            T x;
            T y;
        };
        struct {
            T r;
            T g;
        };
    };

    Matrix<2, 1, T>() : x(T()), y(T()) {}
    Matrix<2, 1, T>(const T& scalar) : x(scalar), y(scalar) {}
    Matrix<2, 1, T>(const T& x, const T& y) : x(x), y(y) {}

    T& operator[](u64 index) {
        switch (index) {
            case 0:
                return this->x;
            case 1:
                return this->y;
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
            default:
                // TODO: Error
                return this->x;
        }
    }

    static T Dot(const Vector2<T>& a, const Vector2<T>& b) {
        return a.x * b.x + a.y * b.y;
    }

    static Vector2<T> Normalise(const Vector2<T>& v) {
        T length = static_cast<T>(sqrt(static_cast<f64>(Vector2<T>::Dot(v, v))));
        if (length != T()) {
            return v / length;
        } else {
            return Vector2<T>();
        }
    }
};

template<typename T>
Vector2<T> operator+(const Vector2<T>& a, const Vector2<T>& b) {
    return {
        a.x + b.x,
        a.y + b.y,
    };
}

template<typename T>
Vector2<T>& operator+=(Vector2<T>& a, const Vector2<T>& b) {
    a = a + b;
    return a;
}

template<typename T>
Vector2<T> operator+(const Vector2<T>& a, const T& b) {
    return {
        a.x + b,
        a.y + b,
    };
}

template<typename T>
Vector2<T> operator+(const T& a, const Vector2<T>& b) {
    return {
        a + b.x,
        a + b.y,
    };
}

template<typename T>
Vector2<T> operator+=(Vector2<T>& a, const T& b) {
    a = a + b;
    return a;
}

template<typename T>
Vector2<T> operator-(const Vector2<T>& a, const Vector2<T>& b) {
    return {
        a.x - b.x,
        a.y - b.y,
    };
}

template<typename T>
Vector2<T>& operator-=(Vector2<T>& a, const Vector2<T>& b) {
    a = a - b;
    return a;
}

template<typename T>
Vector2<T> operator-(const Vector2<T>& a, const T& b) {
    return {
        a.x - b,
        a.y - b,
    };
}

template<typename T>
Vector2<T> operator-(const T& a, const Vector2<T>& b) {
    return {
        a - b.x,
        a - b.y,
    };
}

template<typename T>
Vector2<T> operator-=(Vector2<T>& a, const T& b) {
    a = a - b;
    return a;
}

template<typename T>
Vector2<T> operator*(const Vector2<T>& a, const Vector2<T>& b) {
    return {
        a.x * b.x,
        a.y * b.y,
    };
}

template<typename T>
Vector2<T>& operator*=(Vector2<T>& a, const Vector2<T>& b) {
    a = a * b;
    return a;
}

template<typename T>
Vector2<T> operator*(const Vector2<T>& a, const T& b) {
    return {
        a.x * b,
        a.y * b,
    };
}

template<typename T>
Vector2<T> operator*(const T& a, const Vector2<T>& b) {
    return {
        a * b.x,
        a * b.y,
    };
}

template<typename T>
Vector2<T> operator*=(Vector2<T>& a, const T& b) {
    a = a * b;
    return a;
}

template<typename T>
Vector2<T> operator/(const Vector2<T>& a, const Vector2<T>& b) {
    return {
        a.x / b.x,
        a.y / b.y,
    };
}

template<typename T>
Vector2<T>& operator/=(Vector2<T>& a, const Vector2<T>& b) {
    a = a / b;
    return a;
}

template<typename T>
Vector2<T> operator/(const Vector2<T>& a, const T& b) {
    return {
        a.x / b,
        a.y / b,
    };
}

template<typename T>
Vector2<T> operator/(const T& a, const Vector2<T>& b) {
    return {
        a / b.x,
        a / b.y,
    };
}

template<typename T>
Vector2<T> operator/=(Vector2<T>& a, const T& b) {
    a = a / b;
    return a;
}
