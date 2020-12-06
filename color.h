//
// Created by smiga287 on 02/12/2020.
//

#ifndef PROJECT_RAY_TRACING_COLOR_H
#define PROJECT_RAY_TRACING_COLOR_H

#include "vec3.h"

#include <iostream>
#include "fmt/format.h"
#include <fmt/ostream.h>

class Color : public Vec3 {
public:
    using Vec3::Vec3; // Uses Vec3 constructors
    Color(Vec3 v) : Vec3(v) {}; // allows for implicit conversion

    static void write(const Color& pixel_color, int samples_per_pixel);
};

void Color::write(const Color& pixel_color, int samples_per_pixel) {
    double r = pixel_color.x();
    double g = pixel_color.y();
    double b = pixel_color.z();

    // Divide the color by the number of samples and gamma-correct for gamma=2.0
    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    // Write the translated [0, 255] value of each color component
    int R = static_cast<int>(256 * clamp(r, 0, 0.999));
    int G = static_cast<int>(256 * clamp(g, 0, 0.999));
    int B = static_cast<int>(256 * clamp(b, 0, 0.999));
    fmt::print("{} {} {}\n", R, G, B);
}

#endif //PROJECT_RAY_TRACING_COLOR_H
