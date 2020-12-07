//
// Created by smiga287 on 02/12/2020.
//

#ifndef PROJECT_RAY_TRACING_MATERIAL_H
#define PROJECT_RAY_TRACING_MATERIAL_H

#include "utility.h"
#include "hittable.h"

struct HitRecord;

class Material {
public:
    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material {
private:
    Color albedo;
public:
    Lambertian(const Color& a) : albedo(a) {}

    bool scatter(const Ray &r_in, const HitRecord &rec, Color &attenuation, Ray &scattered) const override {
        // Generate a random scatter direction outside of hit object
        Vec3 scatter_direction = rec.normal + random_unit_vector();
        // Catch degenerate scatter direction
        if (scatter_direction.near_zero()) {
            scatter_direction = rec.normal;
        }

        scattered = Ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }
};

class Metal : public Material {
private:
    Color albedo;
    double fuzz;
public:
    Metal(const Color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

    bool scatter(const Ray &r_in, const HitRecord &rec, Color &attenuation, Ray &scattered) const override {
        Vec3 reflected = reflect(unit_vector(r_in.getDirection()), rec.normal);
        scattered = Ray(rec.p, reflected + fuzz * random_in_unit_sphere()); // fuzzy reflection
        attenuation = albedo;
        // if they are in the same direction, then we had a reflection
        return dot(scattered.getDirection(), rec.normal) > 0;
    }

};

class Dielectric : public Material {
private:
    double ir; // Index of Refraction

    static double reflectance(double cosine, double ref_idx) {
        // Use Schlick's approximation for reflectance
        auto r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }
public:
    Dielectric(double index_of_refraction) : ir(index_of_refraction) {}

    bool scatter(const Ray &r_in, const HitRecord &rec, Color &attenuation, Ray &scattered) const override {
        attenuation = Color(1.0, 1.0, 1.0); // dielectrics absorb no light
        double refraction_ratio = rec.front_face ? (1.0 / ir) : ir;

        // Snell's law
        Vec3 unit_direction = unit_vector(r_in.getDirection());
        double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

        bool cannot_refract = refraction_ratio * sin_theta > 1.0; // there is no solution for Snell's law
        Vec3 direction;
        if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double()) {
            direction = reflect(unit_direction, rec.normal);
        } else {
            direction = refract(unit_direction, rec.normal, refraction_ratio);
        }

        scattered = Ray(rec.p, direction);
        return true;
    }
};

#endif //PROJECT_RAY_TRACING_MATERIAL_H
