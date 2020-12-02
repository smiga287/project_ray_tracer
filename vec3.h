//
// Created by smiga287 on 02/12/2020.
//

#ifndef PROJECT_RAY_TRACING_VEC3_H
#define PROJECT_RAY_TRACING_VEC3_H

#include <cmath>
#include <array>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <iostream>

using std::sqrt;

class Vec3 {
private:
    std::array<double, 3> e;

public:
    Vec3() : e{0,0,0} {}
    Vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
    double operator[] (int i) const { return e[i]; }
    double& operator[] (int i) { return e[i]; }

    Vec3& operator+=(const Vec3& v) {
        e[0] += v.x();
        e[1] += v.y();
        e[2] += v.z();
        return *this;
    }

    Vec3& operator-=(const Vec3& v) {
        e[0] -= v.x();
        e[1] -= v.y();
        e[2] -= v.z();
        return *this;
    }

    Vec3& operator*=(const double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    Vec3& operator*=(const Vec3& v) {
        e[0] *= v.x();
        e[1] *= v.y();
        e[2] *= v.z();
        return *this;
    }

    Vec3& operator/=(const double t) {
        return *this *= 1 / t;
    }

    // Not really needed because fmt is already working with Vec3
    friend std::ostream& operator<<(std::ostream& out, const Vec3& v) {
        return out << v.x() << ' ' << v.y() << ' ' << v.z();
    }

    double length() const {
        return sqrt(length_squared());
    }

    double length_squared() const {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

};

inline Vec3 operator+(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

inline Vec3 operator*(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

inline Vec3 operator*(double t, const Vec3 &v) {
    return Vec3(t * v.x(), t * v.y(), t * v.z());
}

inline Vec3 operator*(const Vec3 &v, double t) {
    return t * v;
}

inline Vec3 operator/(Vec3 v, double t) {
    return (1 / t) * v;
}

inline double dot(const Vec3 &u, const Vec3 &v) {
    return u.x() * v.x()
           + u.y() * v.y()
           + u.z() * v.z();
}

inline Vec3 cross(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.y() * v.z() - u.z() * v.y(),
                u.z() * v.x() - u.x() * v.z(),
                u.x() * v.y() - u.y() * v.x());
}

inline Vec3 unit_vector(Vec3 v) {
    return v / v.length();
}

using Point3 = Vec3; // 3D point

// Vec3 utility functions


#endif //PROJECT_RAY_TRACING_VEC3_H
