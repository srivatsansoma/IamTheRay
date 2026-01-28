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

Vec3 cross_product(Vec3 v1, Vec3 v2) {
    Vec3 result = {
        v1.y*v2.z - v1.z*v2.y,
        -(v1.x*v2.z - v1.z*v2.x),
        v1.x*v2.y - v1.y*v2.x
    };
    return result;
}

Vec3 scalar_mul(Vec3 vec, float scalar){
    Vec3 result = {vec.x*scalar, vec.y*scalar, vec.z*scalar};
    return result;
}

float vec3_mag(Vec3 vec){
    return sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
}

Vec2 get_spherical_angles(Vec3 vec){
    Vec2 angles;
    angles.x = tanh(vec.y/(vec.x + 1e-4));
    angles.y = tanh(sqrt(vec.x*vec.x + vec.y*vec.y)/(vec.z + 1e-4));

    return angles;
}

//angle => [angle on x axis, angle with z axis]
Vec3 give_new_rot_vector(float mag, Vec2 angles){
    Vec3 vec;
    vec.x = mag*sin(angles.y)*cos(angles.x);
    vec.y = mag*sin(angles.y)*sin(angles.x);
    vec.z = mag*cos(angles.y);

    return vec;
}

float distance_point_from_line(Vec3 point, Vec3 ray_direction, Vec3 ray_point){
    return vec3_mag(
        cross_product(
            two_vectors_addorsub(ray_point, ray_direction, SUB),
            ray_direction
        )
    );
}