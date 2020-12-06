//
// Created by smiga287 on 02/12/2020.
//

#ifndef PROJECT_RAY_TRACING_HITTABLE_H
#define PROJECT_RAY_TRACING_HITTABLE_H

#include "utility.h"

class Material;

struct HitRecord {
    Point3 p;
    Vec3 normal;
    shared_ptr<Material> mat_ptr;
    double t{};
    bool front_face{};

    inline void set_face_normal(const Ray& r, const Vec3& outward_normal) {
        front_face = dot(r.getDirection(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Hittable {
public:
    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
};

#endif //PROJECT_RAY_TRACING_HITTABLE_H
