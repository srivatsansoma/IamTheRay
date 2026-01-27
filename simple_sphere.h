#ifndef SIMPLE_SPHERE_H
#define SIMPLE_SPHERE_H

#include "vector3.h"

struct Sphere{
    Vec3 position;
    float radius;
};

Vec4 return_color(Vec2 angle);

#endif

