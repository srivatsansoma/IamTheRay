#include <math.h>

typedef struct{
    float x,y,z;
} Vec3;

typedef enum{
    ADD, SUB
} ADDORSUB;

Vec3 two_vectors_addorsub(Vec3 v1, Vec3 v2, ADDORSUB addorsub){
    if (addorsub == ADD) {
        Vec3 result = {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
        return result;
    }
    Vec3 result = {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
    return result;
}

float dot_product(Vec3 v1, Vec3 v2){
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

Vec3 cross_product(Vec3* v1, Vec3* v2) {
    Vec3 result = {
        v1->y*v2->z - v1->z*v2->y,
        -(v1->x*v2->z - v1->z*v2->z),
        v1->x*v2->y - v1->y*v2->x
    };
    return result;
}

Vec3 scalar_mul(Vec3 vec, float scalar){
    Vec3 result = {vec.x*scalar, vec.y*scalar, vec.z*scalar};
    return result;
}

float vec3_mag(Vec3* vec){
    return sqrt(vec->x*vec->x + vec->y*vec->y + vec->z*vec->z);
}