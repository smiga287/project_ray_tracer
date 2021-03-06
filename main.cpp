#include <fstream>
#include <iostream>

#include "camera.h"
#include "color.h"
#include "fmt/core.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "moving_sphere.h"
#include "utility.h"

Color ray_color(const Ray& r, const Hittable& world, int depth) {
    // If we've exceeded the ray bounce limit, no more light is gathered
    if (depth <= 0) {
        return Color(0, 0, 0);
    }

    HitRecord hit_rec;
    if (world.hit(r, 0.001, infinity, hit_rec)) {
        Ray scattered;
        Color attenuation;
        if (hit_rec.mat_ptr->scatter(r, hit_rec, attenuation, scattered)) {
            // darken the color based on attenuation (how much light was absorbed)
            return attenuation * ray_color(scattered, world, depth - 1);
        }
        // The ray was absorbed therefore we return black
        return Color(0, 0, 0);
    }
    // Returns a linear blend between blue and white depending on the Y value
    Vec3 unit_dir = unit_vector(r.getDirection());
    auto t = 0.5 * (unit_dir.y() + 1.0);
    return (1.0 - t) * Color(1, 1, 1) + t * Color(0.5, 0.7, 1.0);
}

HittableList random_scene() {
    HittableList world;
    auto ground_material = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, ground_material));

    for (int a = -5; a < 5; ++a) {
        for (int b = -5; b < 5; ++b) {
            double choose_mat = random_double();
            Point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if ((center - Point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<Material> sphere_material;
                if (choose_mat < 0.8) {
                    // diffuse
                    Color albedo = Color::random() * Color::random();
                    sphere_material = make_shared<Lambertian>(albedo);
                    Point3 center1 = center + Vec3(0, random_double(0, 0.5), 0);
                    world.add(make_shared<MovingSphere>(center, center1, 0.0, 1.0, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = Color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<Metal>(albedo, fuzz);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<Dielectric>(1.5);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<Dielectric>(1.5);
    world.add(make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<Lambertian>(Color(0.4, 0.7, 0.8));
    world.add(make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

    return world;
}

int main(int argc, char** argv) {
    if (argc > 2) {
        throw std::invalid_argument("Program accepts one or none output arguments");
    }
    std::ofstream output(argc == 2 ? argv[1] : "out.ppm");

    // Image
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    // World
    HittableList world = random_scene();
    // Camera
    Point3 look_from(13, 2, 3);
    Point3 look_at(0, 0, 0);
    Vec3 vup(0, 1, 0); // use world up to keep the camera horizontally level
    double dist_to_focus = 10.0;
    double aperture = 0.1;

    Camera cam(look_from, look_at, vup, 20, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);

    // Render
    fmt::print(output, "P3\n{} {}\n255\n", image_width, image_height);
    for (int j = image_height - 1; j >= 0; --j) {
        fmt::print(stderr, "\rScanLines remaining: {} ", j);
        for (int i = 0; i < image_width; ++i) {
            Color pixel_color(0, 0, 0);
            // Take samples with random disturbance and average it out for antialiasing
            for (int s = 0; s < samples_per_pixel; ++s) {
                double u = (i + random_double()) / (image_width - 1);
                double v = (j + random_double()) / (image_height - 1);
                Ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(output, average_color(pixel_color, samples_per_pixel));
        }
    }
    fmt::print(stderr, "\nDone\n");

    return 0;
}
