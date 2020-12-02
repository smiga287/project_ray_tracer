//
// Created by smiga287 on 02/12/2020.
//

#ifndef PROJECT_RAY_TRACING_COLOR_H
#define PROJECT_RAY_TRACING_COLOR_H

#include "vec3.h"

#include <iostream>
#include "fmt/format.h"
#include <fmt/ostream.h>

class Color : private Vec3 {
    using Vec3::Vec3; // Uses Vec3 constructors

    friend std::ostream& operator<<(std::ostream& out, const Color& c) {
        // Write the translated [0, 255] value of each color component
        const double transl = 255.999;
        return out << static_cast<int>(transl * c.x()) << ' '
            << static_cast<int>(transl * c.y()) << ' '
            << static_cast<int>(transl * c.z()) << '\n';
    }
};

#endif //PROJECT_RAY_TRACING_COLOR_H
