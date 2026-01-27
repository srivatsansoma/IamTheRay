#ifndef BASIC_TRIANGLE_H
#define BASIC_TRIANGLE_H

#include "vector3.h"
#include <string.h>
#include <stdbool.h>

typedef struct {
    Vec3 vertices[3];
    Vec3 normal;
    Vec3 centroid;
    float plane_coeff[4];
    float color[4];
}BasicTriangle ;

void initiate_vertices(Vec3 vertices[3], float color[4], BasicTriangle* tri);
float plane_val(float plane_coeff[4], Vec3 vec);
Vec3 projection_point_on_plane(float plane_coeff[4], Vec3 vec);
bool check_if_inside_triangle(Vec3 vec, BasicTriangle* tri);

#endif

