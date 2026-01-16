#ifndef RT_H_
#define RT_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Vec3 start

typedef struct {
    float e0;
    float e1;
    float e2;
} Vec3;

Vec3 vec3(float x, float y, float z);
float vec3_x(Vec3 v);
float vec3_y(Vec3 v);
float vec3_z(Vec3 v);
float vec3_elem(Vec3 v, int index);
Vec3 vec3_neg(Vec3 v);
Vec3 vec3_sum(Vec3 u, Vec3 v);
Vec3 vec3_diff(Vec3 u, Vec3 v);
Vec3 vec3_mult(Vec3 v, float t);
Vec3 vec3_div(Vec3 v, float t);
Vec3 vec3_prod(Vec3 u, Vec3 v);
float vec3_dot(Vec3 u, Vec3 v);
Vec3 vec3_cross(Vec3 u, Vec3 v);
float vec3_len_sq(Vec3 v);
float vec3_len(Vec3 v);
void vec3_print(Vec3 v);
Vec3 vec3_unit(Vec3 v);

// Vec3 end

// Color start

typedef Vec3 Color;

Color color(float r, float g, float b);
void color_write(Color pixel_color);

// Color end

// Ray start

typedef Vec3 Point3;

typedef struct {
    Point3 origin;
    Vec3 direction;
} Ray;

Point3 point3(float x, float y, float z);
Point3 ray_at(Ray r, float t);

// Ray end

#endif // RT_H_

#ifdef RT_IMPLEMENTATION

// Vec3 start

Vec3 vec3(float x, float y, float z) {
    Vec3 o = {
        .e0 = x,
        .e1 = y,
        .e2 = z,
    };
    return o;
}

float vec3_x(Vec3 v) {
    return v.e0;
}

float vec3_y(Vec3 v) {
    return v.e1;
}

float vec3_z(Vec3 v) {
    return v.e2;
}

float vec3_elem(Vec3 v, int index) {
    switch (index) {
        case 0:
            return v.e0;
        case 1:
            return v.e1;
        case 2:
            return v.e2;
        default:
            perror("index out of bounds");
            exit(EXIT_FAILURE); 
    }
}

Vec3 vec3_neg(Vec3 v) {
    Vec3 o;
    o.e0 = -v.e0;
    o.e1 = -v.e1;
    o.e2 = -v.e2;
    return o;
}

Vec3 vec3_sum(Vec3 u, Vec3 v) {
    Vec3 o;
    o.e0 = u.e0 + v.e0;
    o.e1 = u.e1 + v.e1;
    o.e2 = u.e2 + v.e2;
    return o;
}

Vec3 vec3_diff(Vec3 u, Vec3 v) {
    Vec3 o;
    o.e0 = u.e0 - v.e0;
    o.e1 = u.e1 - v.e1;
    o.e2 = u.e2 - v.e2;
    return o;
}

Vec3 vec3_mult(Vec3 v, float t) {
    Vec3 o;
    o.e0 = v.e0 * t;
    o.e1 = v.e1 * t;
    o.e2 = v.e2 * t;
    return o;
}

Vec3 vec3_div(Vec3 v, float t) {
    float it = (1 / t); 
    Vec3 o;
    o.e0 = v.e0 * it;
    o.e1 = v.e1 * it;
    o.e2 = v.e2 * it;
    return o;
}

Vec3 vec3_prod(Vec3 u, Vec3 v) {
    Vec3 o;
    o.e0 = u.e0 * v.e0;
    o.e1 = u.e1 * v.e1;
    o.e2 = u.e2 * v.e2;
    return o;
}

float vec3_dot(Vec3 u, Vec3 v) {
    return u.e0 * v.e0 + u.e1 * v.e1 + u.e2 * v.e2;
}

Vec3 vec3_cross(Vec3 u, Vec3 v) {
    Vec3 o;
    o.e0 = u.e1 * v.e2 - u.e2 * v.e1;
    o.e1 = u.e2 * v.e0 - u.e0 * v.e2;
    o.e2 = u.e0 * v.e1 - u.e1 * v.e0;
    return o;
}

float vec3_len_sq(Vec3 v) {
    return v.e0 * v.e0 + v.e1 * v.e1 + v.e2 * v.e2;
}

float vec3_len(Vec3 v) {
    return sqrt(vec3_len_sq(v));
}

void vec3_print(Vec3 v) {
    printf("%f %f %f\n", v.e0, v.e1, v.e2);
}

Vec3 vec3_unit(Vec3 v) {
    float length = vec3_len(v);
    return vec3_div(v, length);
}

// Vec3 end

// Color start

Color color(float r, float g, float b) {
    Color o = {
        .e0 = r,
        .e1 = g,
        .e2 = b,
    };
    return o;
}

void color_write(Color pixel_color) {
    float r = vec3_x(pixel_color);
    float g = vec3_y(pixel_color);
    float b = vec3_z(pixel_color);

    int ir = (int) 255.999 * r;
    int ig = (int) 255.999 * g;
    int ib = (int) 255.999 * b;

    printf("%i %i %i\n", ir, ig, ib);
}

// Color end

// Ray start

Point3 point3(float x, float y, float z) {
    Point3 o = {
        .e0 = x,
        .e1 = y,
        .e2 = z,
    };
    return o;
}

Point3 ray_at(Ray r, float t) {
    return vec3_sum(r.origin, vec3_mult(r.direction, t));
}

// Ray end

#endif // RT_IMPLEMENTATION
