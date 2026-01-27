#include "camera.h"

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

    Vec2 ref_angle = get_spherical_angles(camera->camera_screen_dist);

    for (int i = -camera->halfres_x; i < camera->halfres_x; i++){
        for (int j = -camera->halfres_y; j < camera->halfres_y; j++){
            Vec3 relx = scalar_mul(x, i);
            Vec3 rely = scalar_mul(y, j);

            Vec3 ray_normal = two_vectors_addorsub(camera->camera_screen_dist, relx, ADD);
            ray_normal = two_vectors_addorsub(ray_normal, rely, ADD);
            ray_normal = scalar_mul(ray_normal, 1/vec3_mag(&ray_normal));

            Vec2 angle = get_spherical_angles(ray_normal);
            angle.x += ref_angle.x;
            angle.y += ref_angle.y;

            ray_normal = give_new_rot_vector(1, angle);

            initiate_ray(&rays[(i + camera->halfres_x)*camera->halfres_y*2 + (j + camera->halfres_y)], ray_normal, camera->position);
        }
    }

    return rays;
}