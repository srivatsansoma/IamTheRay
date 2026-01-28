#ifndef RAY_H
#define RAY_H

#include "basic_triangle.h"
#include "simple_sphere.h"
#include <stdbool.h>
#include <stdio.h>

struct Ray3 {
    Vec3 normal;
    Vec3 start_point;
    Vec3 last_point;
    Vec3 current_point;
    float color[4];
};

void initiate_ray(struct Ray3* ray, Vec3 normal, Vec3 start_point);
void update_ray_no_check(struct Ray3* ray, float dt);
int check_pass_triangle(struct Ray3* ray, BasicTriangle* tri);
bool reflection(struct Ray3* ray, BasicTriangle* tri, float dt, void* return_addr);
Vec3 point_of_intersection_raywsphere(struct Ray3* ray, struct Sphere* sphere);

#endif

