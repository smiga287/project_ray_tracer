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
public:
    HittableList() = default;
    HittableList(shared_ptr<Hittable> object) : objects{std::move(object)} {}

    void clear() { objects.clear(); }
    void add(shared_ptr<Hittable> object) { objects.push_back(std::move(object)); }

    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

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

#endif //PROJECT_RAY_TRACING_HITTABLE_LIST_H
