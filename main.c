#include <stdio.h>
#include <stdlib.h>

#include "ray.c"

int main(){
    Vec3 vertices[3];
    vertices[0] = (Vec3) {1,0,0};
    vertices[1] = (Vec3) {0,1,0};
    vertices[2] = (Vec3) {0,0,1};

    float color[4] = {255,0,0,1};

    BasicTriangle tri;
    initiate_vertices(vertices, color, &tri);

    struct Ray3 test_ray;
    initiate_ray(&test_ray, (Vec3) {0.5, 0.5, 0.5}, (Vec3) {0,0,0});
    
    int collided = 0;
    Vec3 result[3] = {};
    for (int i=0; i< 100; i ++){
        //printf("%d",reflection(&test_ray, &tri, 0.01, result));
        //printf("%f, %f, %f \n", test_ray.last_point.x, test_ray.last_point.y, test_ray.last_point.z);
        printf("%f %f %f %f \n", test_ray.color[0], test_ray.color[1], test_ray.color[2],  test_ray.color[3]);

        if (reflection(&test_ray, &tri, 0.01, result)){
            test_ray.current_point = result[2];
            test_ray.normal = result[1];
        }
    }

    return 0;
}