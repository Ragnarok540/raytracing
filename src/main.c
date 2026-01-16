#define RT_IMPLEMENTATION
#include "rt.h"

Color ray_color(Ray r) {
    Vec3 unit_direction = vec3_unit(r.direction);
    float a = 0.5 * (vec3_y(unit_direction) + 1.0);
    return vec3_sum(vec3_mult(color(1.0, 1.0, 1.0), 1.0 - a), vec3_mult(color(0.5, 0.7, 1.0), a));
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
    float viewport_width = viewport_height * ((float) image_width / image_height);
    Point3 camera_center = point3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    Vec3 viewport_u = vec3(viewport_width, 0, 0);
    Vec3 viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    Vec3 pixel_delta_u = vec3_div(viewport_u, (float) image_width);
    Vec3 pixel_delta_v = vec3_div(viewport_v, (float) image_height);

    // Calculate the location of the upper left pixel.
    Point3 viewport_upper_left = vec3_diff(camera_center, vec3_diff(vec3(0, 0, focal_length), vec3_diff(vec3_div(viewport_u, 2.0), vec3_div(viewport_v, 2.0))));
    Point3 pixel00_loc = vec3_sum(viewport_upper_left, vec3_mult(vec3_sum(pixel_delta_u, pixel_delta_v), 0.5));

    printf("P3\n%i %i\n255\n", image_width, image_height);

    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            Point3 pixel_center = vec3_sum(pixel00_loc, vec3_sum(vec3_mult(pixel_delta_u, i), vec3_mult(pixel_delta_v, j)));
            Vec3 ray_direction = vec3_diff(pixel_center, camera_center);

            Ray r = {
                .origin = camera_center,
                .direction = ray_direction,
            };

            Color pixel_color = ray_color(r);
            color_write(pixel_color);
        }
    }

    return 0;
}

// bin/ppm > image.ppm
