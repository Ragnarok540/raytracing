#define RT_IMPLEMENTATION
#include "rt.h"

int main(void) {
    int image_width = 256;
    int image_height = 256;

    printf("P3\n%i %i\n255\n", image_width, image_height);

    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            Color pixel_color = {
                .x = (float) i / (image_width - 1),
                .y = (float) j / (image_height - 1),
                .z = 0.0,
            };

            color_write(&pixel_color);
        }
    }

    return 0;
}

// bin/ppm > image.ppm
