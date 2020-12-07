//
// Created by smiga287 on 02/12/2020.
//

#ifndef PROJECT_RAY_TRACING_CAMERA_H
#define PROJECT_RAY_TRACING_CAMERA_H

#include "utility.h"

class Camera {
private:
    Point3 origin;
    Point3 lower_left_corner;
    Vec3 horizontal;
    Vec3 vertical;
    Vec3 w, u, v;
    double lens_radius;
    double time0, time1; // shutter open/close times

public:
    Camera(
            Point3 look_from,
            Point3 look_at,
            Vec3 vup,
            double vert_fov, // vertical field of view in degrees
            double aspect_ratio,
            double aperture,
            double focus_dist,
            double tm0 = 0,
            double tm1 = 0) {

        double theta = degree_to_radians(vert_fov);
        double h = tan(theta / 2);
        double viewport_height = 2.0 * h;
        double viewport_width = aspect_ratio * viewport_height;

        // Create an orthonormal basis
        w = unit_vector(look_from - look_at);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        origin = look_from;
        horizontal = focus_dist * viewport_width * u;
        vertical = focus_dist * viewport_height * v;
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - focus_dist * w;

        lens_radius = aperture / 2;
        time0 = tm0;
        time1 = tm1;
    }

    Ray get_ray(double s, double t) const {
        Vec3 rd = lens_radius * random_int_unit_disk(); // generate defocus blur
        Vec3 offset = u * rd.x() + v * rd.y();
        return Ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset, random_double(time0, time1));
    }
};

#endif //PROJECT_RAY_TRACING_CAMERA_H
