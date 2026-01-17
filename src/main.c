#define RT_IMPLEMENTATION
#include "rt.h"

#include <stdbool.h>

bool hit_sphere(Point3 *center, float radius, Ray *r) {
    Vec3 oc = vec3_diff(r->origin, *center);
    float a = vec3_dot(r->direction, r->direction);
    float b = vec3_dot(r->direction, oc);
    float c = vec3_dot(oc, oc) - radius * radius;
    float discriminant = b * b - a * c;
    return discriminant >= 0;
}

Color ray_color(Ray *r) {
    Point3 sphere_center = point3(0, 0, -1);
    if (hit_sphere(&sphere_center, 0.5, r)) {
        return color(1, 0, 0);
    }

    Vec3 unit_direction = vec3_unit(r->direction);
    float t = 0.5 * (unit_direction.y + 1.0);
    return vec3_lerp(vec3(1, 1, 1), vec3(0.5, 0.7, 1), t);
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
