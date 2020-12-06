//
// Created by smiga287 on 02/12/2020.
//

#ifndef PROJECT_RAY_TRACING_SPHERE_H
#define PROJECT_RAY_TRACING_SPHERE_H

#include "hittable.h"
#include "vec3.h"

class Sphere : public Hittable {
private:
    Point3 center;
    double radius;
    shared_ptr<Material> mat_ptr;
public:
    Sphere() = default;
    Sphere(Point3 cen, double r, shared_ptr<Material> m) : center(cen), radius(r), mat_ptr(std::move(m)) {};
    bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
};

bool Sphere::hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const {
    Vec3 oc = r.getOrigin() - center;
    double a = r.getDirection().length_squared();
    double half_b = dot(oc, r.getDirection());
    double c = oc.length_squared() - radius * radius;
    double discriminant = half_b * half_b - a * c;
    if (discriminant < 0) {
        return false;
    }
    double sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range
    double root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root) {
            return false;
        }
    }
    rec.t = root;
    rec.p = r.at(rec.t);
    Vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}

#endif //PROJECT_RAY_TRACING_SPHERE_H
