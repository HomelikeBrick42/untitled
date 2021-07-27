#pragma once

#include "Core/Defines.hpp"
#include "Math/Math.hpp"

template<u64 Length, typename T>
struct Vector;

template<typename T>
using Vector1 = Vector<1, T>;

using Vector1f = Vector1<f32>;

template<typename T>
struct Vector<1, T> {
    union {
        struct {
            T x;
        };
        struct {
            T r;
        };
    };

    Vector<1, T>() : x(T()) {}
    Vector<1, T>(const T& x) : x(x) {}

    T& operator[](u64 index) {
        switch (index) {
            case 0:
                return this->x;
            default:
                // TODO: Error
                return this->x;
        }
    }

    const T& operator[](u64 index) const {
        switch (index) {
            case 0:
                return this->x;
            default:
                // TODO: Error
                return this->x;
        }
    }

    static T Dot(const Vector1<T>& a, const Vector1<T>& b) {
        return a.x * b.x;
    }

    static Vector1<T> Normalise(const Vector1<T>& v) {
        T length = static_cast<T>(sqrt(static_cast<f64>(Vector1<T>::Dot(v, v))));
        if (length != T()) {
            return v / length;
        } else {
            return Vector1<T>();
        }
    }
};

template<typename T>
Vector1<T> operator+(const Vector1<T>& a, const Vector1<T>& b) {
    return {
        a.x + b.x,
    };
}

template<typename T>
Vector1<T>& operator+=(Vector1<T>& a, const Vector1<T>& b) {
    a = a + b;
    return a;
}

template<typename T>
Vector1<T> operator+(const Vector1<T>& a, const T& b) {
    return {
        a.x + b,
    };
}

template<typename T>
Vector1<T> operator+(const T& a, const Vector1<T>& b) {
    return {
        a + b.x,
    };
}

template<typename T>
Vector1<T> operator+=(Vector1<T>& a, const T& b) {
    a = a + b;
    return a;
}

template<typename T>
Vector1<T> operator-(const Vector1<T>& a, const Vector1<T>& b) {
    return {
        a.x - b.x,
    };
}

template<typename T>
Vector1<T>& operator-=(Vector1<T>& a, const Vector1<T>& b) {
    a = a - b;
    return a;
}

template<typename T>
Vector1<T> operator-(const Vector1<T>& a, const T& b) {
    return {
        a.x - b,
    };
}

template<typename T>
Vector1<T> operator-(const T& a, const Vector1<T>& b) {
    return {
        a - b.x,
    };
}

template<typename T>
Vector1<T> operator-=(Vector1<T>& a, const T& b) {
    a = a - b;
    return a;
}

template<typename T>
Vector1<T> operator*(const Vector1<T>& a, const Vector1<T>& b) {
    return {
        a.x * b.x,
    };
}

template<typename T>
Vector1<T>& operator*=(Vector1<T>& a, const Vector1<T>& b) {
    a = a * b;
    return a;
}

template<typename T>
Vector1<T> operator*(const Vector1<T>& a, const T& b) {
    return {
        a.x * b,
    };
}

template<typename T>
Vector1<T> operator*(const T& a, const Vector1<T>& b) {
    return {
        a * b.x,
    };
}

template<typename T>
Vector1<T> operator*=(Vector1<T>& a, const T& b) {
    a = a * b;
    return a;
}

template<typename T>
Vector1<T> operator/(const Vector1<T>& a, const Vector1<T>& b) {
    return {
        a.x / b.x,
    };
}

template<typename T>
Vector1<T>& operator/=(Vector1<T>& a, const Vector1<T>& b) {
    a = a / b;
    return a;
}

template<typename T>
Vector1<T> operator/(const Vector1<T>& a, const T& b) {
    return {
        a.x / b,
    };
}

template<typename T>
Vector1<T> operator/(const T& a, const Vector1<T>& b) {
    return {
        a / b.x,
    };
}

template<typename T>
Vector1<T> operator/=(Vector1<T>& a, const T& b) {
    a = a / b;
    return a;
}
