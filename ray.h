//
// Created by smiga287 on 02/12/2020.
//

#ifndef PROJECT_RAY_TRACING_RAY_H
#define PROJECT_RAY_TRACING_RAY_H

#include "vec3.h"

class Ray {
private:
    Point3 origin;
    Vec3 direction;
public:
    Ray() = default;
    Ray(const Point3& orig, const Vec3& dir) : origin(orig), direction(dir) {}

    Point3 getOrigin() const { return origin; }
    Vec3 getDirection() const { return direction; }

    Point3 at(double t) const {
        return origin * t * direction;
    }
};

#endif //PROJECT_RAY_TRACING_RAY_H
