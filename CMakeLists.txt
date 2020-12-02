cmake_minimum_required(VERSION 3.17)
project(project_ray_tracing)

set(CMAKE_CXX_STANDARD 20)

add_executable(project_ray_tracing main.cpp vec3.h color.h ray.h)

find_package(fmt)
target_link_libraries(project_ray_tracing fmt::fmt)
