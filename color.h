//
// Created by smiga287 on 02/12/2020.
//

#ifndef PROJECT_RAY_TRACING_COLOR_H
#define PROJECT_RAY_TRACING_COLOR_H

#include "vec3.h"

#include <iostream>
#include "fmt/format.h"
#include <fmt/ostream.h>
#include <fstream>

using Color = Vec3;

Color average_color(const Color& pixel_color, int samples_per_pixel) {
    // Divide the color by the number of samples
    return  (pixel_color * (1.0 / samples_per_pixel));
}

void write_color(std::ofstream& output, Color pixel_color) {
    pixel_color.sqrt(); // gamma-correct for gamma=2.0
    double r = pixel_color.x();
    double g = pixel_color.y();
    double b = pixel_color.z();

    // Write the translated [0, 255] value of each color component
    int R = static_cast<int>(256 * clamp(r, 0, 0.999));
    int G = static_cast<int>(256 * clamp(g, 0, 0.999));
    int B = static_cast<int>(256 * clamp(b, 0, 0.999));
    fmt::print(output,"{} {} {}\n", R, G, B);
}

#endif //PROJECT_RAY_TRACING_COLOR_H
