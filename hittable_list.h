//
// Created by smiga287 on 02/12/2020.
//

#ifndef PROJECT_RAY_TRACING_HITTABLE_LIST_H
#define PROJECT_RAY_TRACING_HITTABLE_LIST_H

#include <memory>
#include <vector>

#include "utility.h"
#include "hittable.h"

class HittableList : public Hittable {
private:
    std::vector<shared_ptr<Hittable>> objects;
    friend class BVHNode;
public:
    HittableList() = default;
    HittableList(shared_ptr<Hittable> object) : objects{std::move(object)} {}

    void clear() { objects.clear(); }
    void add(shared_ptr<Hittable> object) { objects.push_back(std::move(object)); }

    bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

    bool bounding_box(double time0, double time1, AABB &output_box) const override;
};

bool HittableList::hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const {
    HitRecord temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;

    for (const auto& object : objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

bool HittableList::bounding_box(double time0, double time1, AABB &output_box) const {
    if (objects.empty()) {
        return false;
    }
    AABB temp_box;
    bool first_box;

    for (const auto& object : objects) {
        if (!object->bounding_box(time0, time1, temp_box)) {
            return false;
        }
        output_box = first_box ? temp_box : surrounding_box(output_box, temp_box);
        first_box = false;
    }
    return true;
}

#endif //PROJECT_RAY_TRACING_HITTABLE_LIST_H
