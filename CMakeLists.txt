cmake_minimum_required(VERSION 3.17)
project(project_ray_tracing)

set(CMAKE_CXX_STANDARD 20)

add_executable(project_ray_tracing main.cpp vec3.h color.h ray.h hittable.h sphere.h hittable_list.h utility.h camera.h material.h moving_sphere.h aabb.h bvh.h texture.h)

find_package(fmt)
target_link_libraries(project_ray_tracing fmt::fmt)
