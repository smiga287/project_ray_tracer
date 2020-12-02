#include <iostream>
#include "fmt/core.h"
#include "vec3.h"
#include "color.h"

int main() {
    // Image
    const int image_width = 256;
    const int image_height = 256;

    // Render

    fmt::print("P3\n{} {}\n255\n", image_width, image_height);

    for (int j = image_height - 1; j >= 0; --j) {
         fmt::print(stderr, "\rScanLines remaining: {} ", j);
//        std::cerr << "\rScanLines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            Color pixel_color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0.25);
            fmt::print("{}\n", pixel_color);
        }
    }
    fmt::print(stderr, "\nDone\n");

    return 0;
}
