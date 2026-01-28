#ifndef VECTOR3_H
#define VECTOR3_H

#include <math.h>

typedef struct{
    float x,y,z;
} Vec3;

typedef struct {
    float x, y;
}Vec2;

typedef struct {
    float x, y, z, w;
} Vec4;

typedef enum{
    ADD, SUB
} ADDORSUB;

Vec3 two_vectors_addorsub(Vec3 v1, Vec3 v2, ADDORSUB addorsub);
float dot_product(Vec3 v1, Vec3 v2);
Vec3 cross_product(Vec3 v1, Vec3 v2);
Vec3 scalar_mul(Vec3 vec, float scalar);
float vec3_mag(Vec3 vec);
Vec2 get_spherical_angles(Vec3 vec);
Vec3 give_new_rot_vector(float mag, Vec2 angles);
float distance_point_from_line(Vec3 point, Vec3 ray_direction, Vec3 ray_point);

#endif

