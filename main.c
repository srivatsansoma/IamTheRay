#include <stdio.h>
#include <stdlib.h>

#include "camera.c"

int main(){
    Vec3 vertices[3];
    vertices[0] = (Vec3) {1,0,0};
    vertices[1] = (Vec3) {0,1,0};
    vertices[2] = (Vec3) {0,0,1};

    float color[4] = {255,0,0,1};

    BasicTriangle tri;
    initiate_vertices(vertices, color, &tri);

    struct Ray3* rays_test;
    struct Camera cam_test= {(Vec3){0,0,0}, (Vec3){0,10,20}, 100,100,100,100};
    rays_test = initiate_camera_rays(&cam_test);

    for (int i = 0 ; i < 200*200; i++){
        struct Ray3 *test_ray = rays_test + i;
        printf("%f, %f, %f \n", test_ray->normal.x, test_ray->normal.y, test_ray->normal.z);
    }
}