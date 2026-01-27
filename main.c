#include <stdio.h>
#include <stdlib.h>

#include "camera.h"
#include "basic_triangle.h"
#include "simple_sphere.h"

int main(){
    int HALFRES_X = 10;
    int HALFRES_Y = 10;

    Vec3 vertices[3];
    vertices[0] = (Vec3) {1,0,0};
    vertices[1] = (Vec3) {0,1,0};
    vertices[2] = (Vec3) {0,0,1};

    float color[4] = {255,0,0,1};

    BasicTriangle tri;
    initiate_vertices(vertices, color, &tri);

    struct Ray3* rays_test;
    struct Camera cam_test= {(Vec3){0,0,0}, (Vec3){0,0,-200}, 10,10,HALFRES_X, HALFRES_Y};
    struct Sphere sphere_test = {(Vec3) {0,0,0}, 100};
    rays_test = initiate_camera_rays(&cam_test);

    for (int i = 0 ; i < HALFRES_X*HALFRES_Y; i++){
        struct Ray3 *test_ray = rays_test + i;
        //printf("%f, %f, %f \n", test_ray->normal.x, test_ray->normal.y, test_ray->normal.z);

        Vec3 collison_point = point_of_intersection_raywsphere(test_ray, &sphere_test);

        printf("%d %f %f %f \n" , i, collison_point.x, collison_point.y, collison_point.z);
    }
}