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
    bool hit(const Ray& r, double t_min, double t_max, HitRecord& hit_rec) const override;
};

inline bool is_in_range(double x, double min, double max) {
    return x >= min && x <= max;
}

bool Sphere::hit(const Ray &r, double t_min, double t_max, HitRecord &hit_rec) const {
    // Point O - origin
    // Point P - random point
    // Point C - Sphere center
    // double r - Sphere radius
    // Sphere S(r, C)
    // P in S := (x - C.x)^2 + (y - C.y)^2 + (z - C.z)^2 == r^2
    // Ray R(origin: O, dir: Vec3(O, P))
    // P = R(t)
    // ==> R in S := (R(t).x - C.x)^2 + (R(t).y - C.y)^2 + (R(t).z - C.z)^2 == r^2
    //               (R(t) - C) . (R(t) - C) == r^2
    //               (O + td - C) . (O + td - C) == r^2
    //               t^2d.d + 2td.(O - C) + (O - C).(O - C) - r^2 == 0
    //               (d.d)t^2 + 2(d.CO)t + (CO.CO - r^2) == 0
    //                 a           b             c
    //               t1,2 = (-b +- sqrt(b^2 - 4ac)) / 2a, b = 2 * half_b
    //               t1,2 = (-half_b +- sqrt(b^2 - ac)) / a

    Vec3 co = r.getOrigin() - center;
    double a = r.getDirection().length_squared();
    double half_b = dot(co, r.getDirection());
    double c = co.length_squared() - radius * radius;
    double discriminant = half_b * half_b - a * c;
    if (discriminant < 0) { // no solutions => ray doesn't hit the sphere
        return false;
    }
    double discr_sqrt = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range
    double root = (-half_b - discr_sqrt) / a;
    if (!is_in_range(root, t_min, t_max)) {
        root = (-half_b + discr_sqrt) / a;
        if (!is_in_range(root, t_min, t_max)) {
            return false;
        }
    }

    hit_rec.t = root; // parameter t of the ray at which sphere is hit
    hit_rec.p = r.at(hit_rec.t); // Ray R(t) => point of intersection between ray and sphere
    Vec3 outward_normal = (hit_rec.p - center) / radius; // normed normal on the sphere surface
    hit_rec.set_face_normal(r, outward_normal);
    hit_rec.mat_ptr = mat_ptr;

    return true;
}

#endif //PROJECT_RAY_TRACING_SPHERE_H
