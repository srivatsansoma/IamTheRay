#include "ray.c"

struct Camera{
    Vec3 position;
    Vec3 camera_screen_dist;
    float width, hiegth;
    int halfres_x, halfres_y;
};

struct Ray3* initiate_camera_rays(struct Camera* camera){
    struct Ray3* rays = malloc(4*camera->halfres_x*camera->halfres_y * sizeof(struct Ray3));
    Vec3 x = scalar_mul((Vec3){1,0,0}, camera->width/camera->halfres_x/2);
    Vec3 y = scalar_mul((Vec3){0,1,0}, camera->width/camera->halfres_y/2);

    for (int i = -camera->halfres_x; i < camera->halfres_x; i++){
        for (int j = -camera->halfres_y; j < camera->halfres_y; j++){
            Vec3 relx = scalar_mul(x, i);
            Vec3 rely = scalar_mul(y, j);

            Vec3 ray_normal = two_vectors_addorsub(camera->position, relx, ADD);
            ray_normal = two_vectors_addorsub(ray_normal, rely, ADD);
            initiate_ray(&rays[(i + camera->halfres_x)*camera->halfres_y*2 + (j + camera->halfres_y)], ray_normal, camera->position);
        }
    }

    return rays;
}