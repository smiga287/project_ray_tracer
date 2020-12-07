//
// Created by smiga287 on 02/12/2020.
//

#ifndef PROJECT_RAY_TRACING_HITTABLE_H
#define PROJECT_RAY_TRACING_HITTABLE_H

#include "utility.h"
#include "aabb.h"

class Material;

struct HitRecord {
    Point3 p;
    Vec3 normal;
    shared_ptr<Material> mat_ptr;
    double t{};
    bool front_face{};

    inline void set_face_normal(const Ray& r, const Vec3& outward_normal) {
        // if the ray and normal face different directions then the ray is outside of the object
        // if the dot product of ray and normal is negative then the ray and normal face different directions
        // we want the normal to always be outward
        front_face = dot(r.getDirection(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Hittable {
public:
    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
    virtual bool bounding_box(double time0, double time1, AABB& output_box) const = 0;
};

#endif //PROJECT_RAY_TRACING_HITTABLE_H
