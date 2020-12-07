//
// Created by smiga287 on 07/12/2020.
//

#ifndef PROJECT_RAY_TRACING_MOVING_SPHERE_H
#define PROJECT_RAY_TRACING_MOVING_SPHERE_H


#include "hittable.h"
#include "vec3.h"

class MovingSphere : public Hittable {
private:
    Point3 center0, center1;
    double radius;
    shared_ptr<Material> mat_ptr;
    double time0, time1;
public:
    MovingSphere() = default;
    MovingSphere(Point3 cen0, Point3 cen1, double tm0, double tm1, double r, shared_ptr<Material> m)
        : center0(cen0), center1(cen1), time0(tm0), time1(tm1), radius(r), mat_ptr(std::move(m)) {};
    bool hit(const Ray& r, double t_min, double t_max, HitRecord& hit_rec) const override;
    Point3 getCurCenter(double time) const;

    bool bounding_box(double time0, double time1, AABB &output_box) const override;
};

Point3 MovingSphere::getCurCenter(double time) const {
    return  center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}

bool MovingSphere::hit(const Ray &r, double t_min, double t_max, HitRecord &hit_rec) const {
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

    Vec3 co = r.getOrigin() - getCurCenter(r.getTime());
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
    Vec3 outward_normal = (hit_rec.p - getCurCenter(r.getTime())) / radius; // normed normal on the sphere surface
    hit_rec.set_face_normal(r, outward_normal);
    hit_rec.mat_ptr = mat_ptr;

    return true;
}

bool MovingSphere::bounding_box(double time0, double time1, AABB &output_box) const {
    auto R = Vec3(radius, radius, radius);
    auto box0 = AABB(getCurCenter(time0) - R, getCurCenter(time0) + R);
    auto box1 = AABB(getCurCenter(time1) - R, getCurCenter(time1) + R);
    output_box = surrounding_box(box0, box1);
    return true;
}


#endif //PROJECT_RAY_TRACING_MOVING_SPHERE_H
