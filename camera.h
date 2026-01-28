#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#include <stdlib.h>
#include <stdio.h>

struct Camera{
    Vec3 position;
    Vec3 camera_screen_dist;
    float width, hiegth;
    int halfres_x, halfres_y;
};

struct Ray3* initiate_camera_rays(struct Camera* camera);

#endif

