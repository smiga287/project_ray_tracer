//
// Created by smiga287 on 07/12/2020.
//

#ifndef PROJECT_RAY_TRACING_AABB_H
#define PROJECT_RAY_TRACING_AABB_H

#include "utility.h"

class AABB {
private:
    Point3 minimum;
    Point3 maximum;
public:
    AABB() = default;
    AABB(const Point3& min, const Point3& max) : minimum(min), maximum(max) {}

    Point3 getMin() const { return minimum; }
    Point3 getMax() const { return maximum; }

    bool hit(const Ray& r, double t_min, double t_max) const {
        for (int a = 0; a < 3; a++) {
            double invD = 1.0 / r.getDirection()[a];
            double t0 = (minimum[a] - r.getOrigin()[a]) * invD;
            double t1 = (maximum[a] - r.getOrigin()[a]) * invD;
            if (invD < 0.0) {
               std::swap(t0, t1);
            }
            t_min = t0 > t_min ? t0 : t_min;
            t_max = t1 < t_max ? t1 : t_max;
            if (t_max <= t_min) {
                return false;
            }
        }
        return true;
    }
};

AABB surrounding_box(const AABB& box0, const AABB& box1) {
   Point3 small(fmin(box0.getMin().x(), box1.getMin().x()),
                fmin(box0.getMin().y(), box1.getMin().y()),
                fmin(box0.getMin().z(), box1.getMin().z()));

   Point3 big(fmax(box0.getMax().x(), box1.getMax().x()),
              fmax(box0.getMax().y(), box1.getMax().y()),
              fmax(box0.getMax().z(), box1.getMax().z()));

   return AABB(small, big);
}

#endif //PROJECT_RAY_TRACING_AABB_H
