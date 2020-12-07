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
    double time;
public:
    Ray() = default;
    Ray(const Point3& orig, const Vec3& dir, double tm = 0.0) : origin(orig), direction(dir), time(tm) {}

    Point3 getOrigin() const { return origin; }
    Vec3 getDirection() const { return direction; }
    double getTime() const { return time; }

    Point3 at(double t) const {
        return origin + t * direction;
    }
};

#endif //PROJECT_RAY_TRACING_RAY_H
