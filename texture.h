//
// Created by smiga287 on 07/12/2020.
//

#ifndef PROJECT_RAY_TRACING_TEXTURE_H
#define PROJECT_RAY_TRACING_TEXTURE_H

#include "utility.h"

class Texture {
public:
    virtual Color value(double u, double v, const Point3& p) const = 0;
};

class SolidColor : public Texture {
private:
    Color color_value;
public:
    SolidColor() = default;
    SolidColor(Color c) : color_value(c) {}
    SolidColor(double red, double green, double blue) : SolidColor(Color(red, green, blue)) {}

    Color value(double u, double v, const Point3 &p) const override {
        return color_value;
    }

};

#endif //PROJECT_RAY_TRACING_TEXTURE_H
