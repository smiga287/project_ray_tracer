//
// Created by smiga287 on 02/12/2020.
//

#ifndef PROJECT_RAY_TRACING_UTILITY_H
#define PROJECT_RAY_TRACING_UTILITY_H
#include <cmath>
#include <random>
#include <limits>
#include <memory>

// Usings
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility functions
inline double degree_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0, 1);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min, max)
    return min + (max - min) * random_double();
}

inline double clamp(double x, double min, double max) {
    if (x < min) { return min; }
    if (x > max) { return max; }
    return x;
}

// Common headers
#include "ray.h"
#include "vec3.h"
#include "color.h"

#endif //PROJECT_RAY_TRACING_UTILITY_H
