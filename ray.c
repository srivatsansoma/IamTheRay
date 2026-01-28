#include "ray.h"

struct Ray3 {
    Vec3 normal;
    Vec3 start_point;
    Vec3 last_point;
    Vec3 current_point;
    float color[4];
};

void initiate_ray(struct Ray3* ray, Vec3 normal, Vec3 start_point){
    ray->normal = normal;
    ray->start_point = start_point;
    ray->last_point = start_point;
    ray->current_point = start_point;
}

void update_ray_no_check(struct Ray3* ray, float dt){
    Vec3 update;
    update = scalar_mul(ray->normal, dt);
    ray->last_point = ray->current_point;
    ray->current_point = two_vectors_addorsub(ray->current_point, update, ADD);
}

int check_pass_triangle(struct Ray3* ray, BasicTriangle* tri){
    float s1 = plane_val(tri->plane_coeff, ray->current_point);
    float s2 = plane_val(tri->plane_coeff, ray->last_point);

    if ((s1>0 && s2<0) || (s2>0 && s1>0)) return 1;
    return 0;
}

bool reflection(struct Ray3* ray, BasicTriangle* tri, float dt, void* return_addr){
    update_ray_no_check(ray, dt);

    if (!check_pass_triangle(ray, tri)) return false;

    Vec3 projection_point = projection_point_on_plane(tri->plane_coeff, ray->normal);
    if (check_if_inside_triangle(projection_point, tri)) return false;

    *ray->color = *tri->color;

    Vec3 new_normal = two_vectors_addorsub(
        ray->normal,
        scalar_mul(tri->normal, 2*dot_product(ray->normal, tri->normal)),
        SUB
    );

    Vec3 new_current_point = two_vectors_addorsub(
        scalar_mul(projection_point, 2),
        ray->current_point,
        SUB
    );

    Vec3 result[3] = {projection_point, new_normal, new_current_point};

    memcpy(return_addr, result, sizeof(Vec3)*3);

    return true;
}

Vec3 point_of_intersection_raywsphere(struct Ray3* ray, struct Sphere* sphere){
    Vec3 ray_to_center = two_vectors_addorsub(sphere->position, ray->current_point, SUB);
    
    float poly_a = dot_product(ray->normal, ray->normal);
    float poly_b = -2*dot_product(ray->normal, ray_to_center);
    float poly_c = dot_product(ray_to_center, ray_to_center) - sphere->radius*sphere->radius;

    float poly_sqrt_discriminant = poly_b*poly_b - 4*poly_a*poly_c;
    if (poly_sqrt_discriminant < 0) return (Vec3){0,0,0};
    poly_sqrt_discriminant = sqrt(poly_sqrt_discriminant);

    float t1 = (-poly_b + poly_sqrt_discriminant)/(2*poly_a);
    float t2 = (-poly_b - poly_sqrt_discriminant)/(2*poly_a);

    float t;
    if (t1 > 0 && t2 > 0)
        t = (t1 < t2) ? t1 : t2;
    else if (t1 > 0)
        t = t1;
    else if (t2 > 0)
        t = t2;
    else
        return (Vec3){0,0,0};

    return two_vectors_addorsub(ray->current_point,
                                scalar_mul(ray->normal, t),
                                ADD);
}