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
#include "utility.h"

using std::sqrt;
using std::fabs;

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

    double length() const {
        return std::sqrt(length_squared());
    }

    double length_squared() const {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    bool near_zero() const {
        // Return true if the vector is close to zero in all dimensions
        const double s = 1e-8;
        return (fabs(this->x()) < s) && (fabs(this->y()) < s) && (fabs(this->z()) < s);
    }

    void sqrt() {
        e[0] = std::sqrt(e[0]);
        e[1] = std::sqrt(e[1]);
        e[2] = std::sqrt(e[2]);
    }


    inline static Vec3 random() {
        return Vec3(random_double(), random_double(), random_double());
    }

    inline static Vec3 random(double min, double max) {
        return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }

};

// Vec3 utility functions

// Not really needed because fmt is already working with Vec3
inline std::ostream& operator<<(std::ostream& out, const Vec3& v) {
    return out << v.x() << ' ' << v.y() << ' ' << v.z();
}
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

inline Vec3 operator/(const Vec3& v, double t) {
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

inline Vec3 unit_vector(const Vec3& v) {
    return v / v.length();
}

Vec3 random_int_unit_disk() {
    while (true) {
        Vec3 p(random_double(-1, 1), random_double(-1, 1), 0);
        if (p.length_squared() >= 1) {
            continue;
        }
        return p;
    }
}

Vec3 random_in_unit_sphere() {
    // Generate a random vector in unit cube and take it iff it's in unit sphere
    while (true) {
        auto p = Vec3::random(-1, 1);
        if (p.length_squared() >= 1) {
            continue;
        }
        return p;
    }
}

Vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}


Vec3 reflect(const Vec3& v, const Vec3& n) {
    return v - 2 * dot(v, n) * n;
}

Vec3 refract(const Vec3& uv, const Vec3& n, double etai_over_etat) {
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    Vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
    Vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

using Point3 = Vec3; // 3D point

#endif //PROJECT_RAY_TRACING_VEC3_H
