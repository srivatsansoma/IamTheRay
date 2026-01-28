#include "vector3.h"

struct Sphere{
    Vec3 position;
    float radius;
};

Vec4 return_color(struct Sphere* sphere ,Vec2 angle){
    return (Vec4) {0,255,0,1};
}

