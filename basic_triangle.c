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

void initiate_vertices(Vec3 vertices[3], float color[4], BasicTriangle* tri){
    memcpy(tri->vertices, vertices, sizeof(Vec3)*3);

    memcpy(tri->color, color, 4*sizeof(float));

    Vec3 ab = two_vectors_addorsub(tri->vertices[1], tri->vertices[0], SUB);
    Vec3 ac = two_vectors_addorsub(tri->vertices[2], tri->vertices[0], SUB);

    tri->normal = cross_product(ab, ac);
    tri->normal = scalar_mul(tri->normal, 1/vec3_mag(tri->normal));

    memcpy(tri->plane_coeff, &tri->normal, 3*sizeof(float));
    tri->plane_coeff[3] = -(
        tri->vertices[0].x*tri->normal.x
        + tri->vertices[0].y*tri->normal.y
        + tri->vertices[0].z*tri->normal.z
    );

    Vec3 centroid = two_vectors_addorsub(
        scalar_mul(vertices[0], 1/3),
        scalar_mul(vertices[1], 1/3),
        ADD
    );
    centroid = two_vectors_addorsub(
        centroid,
        scalar_mul(vertices[2], 1/3),
        ADD
    );
}

float plane_val(float plane_coeff[4], Vec3 vec){
    return (plane_coeff[0]*vec.x + plane_coeff[1]*vec.y + plane_coeff[2]*vec.z + plane_coeff[3]);
}

Vec3 projection_point_on_plane(float plane_coeff[4], Vec3 vec){
    float lambda = -plane_val(plane_coeff, vec)/(
        plane_coeff[0]*plane_coeff[0]
        + plane_coeff[1]*plane_coeff[1]
        + plane_coeff[2]*plane_coeff[2]
    );

    return (Vec3){
        vec.x + lambda*plane_coeff[0],
        vec.y + lambda*plane_coeff[1],
        vec.z + lambda*plane_coeff[2]
    };
}

bool check_if_inside_triangle(Vec3 vec, BasicTriangle* tri){
    Vec3 v0 = two_vectors_addorsub(tri->vertices[1], tri->vertices[2], SUB);
    Vec3 v1 = two_vectors_addorsub(tri->vertices[2], tri->vertices[0], SUB);
    Vec3 v2 = two_vectors_addorsub(vec,              tri->vertices[0], SUB);

    float d00 = dot_product(v0,v0);
    float d01 = dot_product(v0,v1);
    float d02 = dot_product(v0,v2);
    float d11 = dot_product(v1,v1);
    float d12 = dot_product(v2,v1);

    float denom = d00*d11 - d01*d01;

    float beta  = (d11*d02 - d12*d01)/denom;
    float gamma = (d00*d12 - d01*d02)/denom;
    float alpha = 1 - beta- gamma;

    if (beta >= 0 && gamma>=0 && alpha>=0) return true;
    return false;
}