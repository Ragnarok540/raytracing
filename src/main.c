#define RT_IMPLEMENTATION
#include "rt.h"

#include <stdbool.h>

float hit_sphere(Point3 *center, float radius, Ray *r) {
    Vec3 oc = vec3_diff(*center, r->origin);
    float a = vec3_len_sq(r->direction);
    float h = vec3_dot(r->direction, oc);
    float c = vec3_len_sq(oc) - radius * radius;
    float discriminant = h * h - a * c;

    if (discriminant < 0) {
        return -1.0;
    } else {
        return (h - sqrt(discriminant)) / a;
    }
}

Color ray_color(Ray *r) {
    Point3 sphere_center = point3(0, 0, -1);
    float t =  hit_sphere(&sphere_center, 0.5, r);
    
    if (t > 0) {
        Vec3 n = vec3_unit(vec3_diff(ray_at(*r, t), vec3(0, 0, -1)));
        return vec3_mult(color(n.x + 1, n.y + 1, n.z +1 ), 0.5);
    }

    Vec3 unit_direction = vec3_unit(r->direction);
    t = 0.5 * (unit_direction.y + 1.0);
    return vec3_lerp(color(1.0, 1.0, 1.0), color(0.5, 0.7, 1.0), t);
}

int main(void) {
    // Image

    float aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = (int) image_width / aspect_ratio;
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera

    float focal_length = 1.0;
    float viewport_height = 2.0;
    float viewport_width = viewport_height * aspect_ratio;
    Point3 origin = point3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    Vec3 horizontal = vec3(viewport_width, 0, 0);
    Vec3 vertical = vec3(0, -viewport_height, 0);

    Point3 lower_left_corner = origin;
    vec3_sub(&lower_left_corner, vec3_mult(horizontal, 0.5));
    vec3_sub(&lower_left_corner, vec3_mult(vertical, 0.5));
    vec3_sub(&lower_left_corner, vec3(0, 0, focal_length));

    printf("P3\n%i %i\n255\n", image_width, image_height);

    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            float u = (float) i / (image_width - 1);
            float v = (float) j / (image_height - 1);

            Point3 ray_direction = lower_left_corner;
            vec3_add(&ray_direction, vec3_mult(horizontal, u));
            vec3_add(&ray_direction, vec3_mult(vertical, v));
            vec3_sub(&ray_direction, origin);
            
            Ray r = ray(origin, ray_direction);
            Color pixel_color = ray_color(&r);
            color_write(&pixel_color);
        }
    }

    return 0;
}

// bin/main > sphere.ppm
