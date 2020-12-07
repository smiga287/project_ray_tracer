//
// Created by smiga287 on 07/12/2020.
//

#ifndef PROJECT_RAY_TRACING_BVH_H
#define PROJECT_RAY_TRACING_BVH_H

#include "utility.h"
#include "hittable.h"
#include "hittable_list.h"
#include "fmt/core.h"

class BVHNode : public Hittable {
private:
    shared_ptr<Hittable> left;
    shared_ptr<Hittable> right;
    AABB box;

public:
    BVHNode() = default;
    BVHNode(const HittableList& list, double time0, double time1)
        : BVHNode(list.objects, 0, list.objects.size(), time0, time1) {}
    BVHNode(const std::vector<shared_ptr<Hittable>>& src_objects, size_t start, size_t end, double time0, double time1);

    bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const override;

    bool bounding_box(double time0, double time1, AABB &output_box) const override;
};

inline bool box_compare(const shared_ptr<Hittable>& a, const shared_ptr<Hittable>& b, int axis) {
    AABB box_a;
    AABB box_b;

    if (!a->bounding_box(0, 0, box_a) || !b->bounding_box(0, 0, box_b)) {
        fmt::print(stderr, "No bounding box in BVHNode constructor");
    }
    return box_a.getMin()[axis] < box_b.getMin()[axis];
}

bool box_x_compare(const shared_ptr<Hittable>& a, const shared_ptr<Hittable>& b) {
    return box_compare(a, b, 0);
}

bool box_y_compare(const shared_ptr<Hittable>& a, const shared_ptr<Hittable>& b) {
    return box_compare(a, b, 1);
}

bool box_z_compare(const shared_ptr<Hittable>& a, const shared_ptr<Hittable>& b) {
    return box_compare(a, b, 2);
}



BVHNode::BVHNode(const std::vector<shared_ptr<Hittable>> &src_objects, size_t start, size_t end, double time0,
                 double time1) {
    auto objects = src_objects; // Create a modifiable array of source objects

    int axis = random_int(0, 2);
    auto comparator = (axis == 0) ? box_x_compare
                    : (axis == 1) ? box_y_compare
                                  : box_z_compare;

    size_t object_span = end - start;
    if (object_span == 1) {
        left = right = objects[start];
    } else if (object_span == 2) {
        if (comparator(objects[start], objects[start + 1])) {
            left = objects[start];
            right = objects[start + 1];
        } else {
            left = objects[start + 1];
            right = objects[start];
        }
    } else {
        std::sort(objects.begin() + start, objects.begin() + end, comparator);
        auto mid = start + object_span / 2;
        left = make_shared<BVHNode>(objects, start, mid, time0, time1);
        right = make_shared<BVHNode>(objects, mid, end, time0, time1);
    }
    AABB box_left, box_right;
    if (!left->bounding_box(time0, time1, box_left) ||
        !right->bounding_box(time0, time1, box_right)) {
       fmt::print(stderr, "No bounding box in BVHNode constructor");
    }
}

bool BVHNode::hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const {
    if (!box.hit(r, t_min, t_max)) {
        return false;
    }

    bool hit_left = left->hit(r, t_min, t_max, rec);
    bool hit_right = right->hit(r, t_min, hit_left ? rec.t : t_max, rec);

    return hit_left || hit_right;
}

bool BVHNode::bounding_box(double time0, double time1, AABB &output_box) const {
    output_box = box;
    return true;
}

#endif //PROJECT_RAY_TRACING_BVH_H
