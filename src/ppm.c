#include <stdio.h>

int main(void) {
    int image_width = 256;
    int image_height = 256;

    printf("P3\n%i %i\n255\n", image_width, image_height);

    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            float r = (float) i / (image_width - 1);
            float g = (float) j / (image_height - 1);
            float b = 0.0;

            int ir = (int) 255.999 * r;
            int ig = (int) 255.999 * g;
            int ib = (int) 255.999 * b;

            printf("%i %i %i\n", ir, ig, ib);
        }
    }

    return 0;
}

// bin/ppm > image.ppm
