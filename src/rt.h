#ifndef RT_H_
#define RT_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Vec3 start

typedef struct {
    float x;
    float y;
    float z;
} Vec3;

Vec3 vec3(float x, float y, float z);
Vec3 vec3_neg(Vec3 v);
void vec3_add(Vec3 *u, Vec3 v);
void vec3_sub(Vec3 *u, Vec3 v);
void vec3_scale(Vec3 *v, float t);
Vec3 vec3_sum(Vec3 u, Vec3 v);
Vec3 vec3_diff(Vec3 u, Vec3 v);
Vec3 vec3_prod(Vec3 u, Vec3 v);
Vec3 vec3_mult(Vec3 v, float t);
float vec3_dot(Vec3 u, Vec3 v);
Vec3 vec3_cross(Vec3 u, Vec3 v);
float vec3_len_sq(Vec3 v);
float vec3_len(Vec3 v);
void vec3_print(Vec3 v);
Vec3 vec3_unit(Vec3 v);
Vec3 vec3_lerp(Vec3 from, Vec3 to, float t);

// Vec3 end

// Color start

typedef Vec3 Color;

Color color(float r, float g, float b);
void color_write(Color *pixel_color);

// Color end

// Ray start

typedef Vec3 Point3;

typedef struct {
    Point3 origin;
    Vec3 direction;
} Ray;

Point3 point3(float x, float y, float z);
Ray ray(Point3 origin, Vec3 direction);
Point3 ray_at(Ray r, float t);

// Ray end

#endif // RT_H_

#ifdef RT_IMPLEMENTATION

// Vec3 start

Vec3 vec3(float x, float y, float z) {
    Vec3 result = {
        .x = x,
        .y = y,
        .z = z,
    };
    return result;
}

Vec3 vec3_neg(Vec3 v) {
    Vec3 result = {
        .x = -v.x,
        .y = -v.y,
        .z = -v.z,
    };
    return result;
}

void vec3_add(Vec3 *u, Vec3 v) {
    u->x += v.x;
    u->y += v.y;
    u->z += v.z;
}

void vec3_sub(Vec3 *u, Vec3 v) {
    u->x -= v.x;
    u->y -= v.y;
    u->z -= v.z;
}

void vec3_scale(Vec3 *v, float t) {
    v->x *= t;
    v->y *= t;
    v->z *= t;
}

Vec3 vec3_sum(Vec3 u, Vec3 v) {
    return vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}

Vec3 vec3_diff(Vec3 u, Vec3 v) {
    return vec3(u.x - v.x, u.y - v.y, u.z - v.z);
}

Vec3 vec3_prod(Vec3 u, Vec3 v) {
    return vec3(u.x * v.x, u.y * v.y, u.z * v.z);
}

Vec3 vec3_mult(Vec3 v, float t) {
    return vec3(v.x * t, v.y * t, v.z * t);
}

float vec3_dot(Vec3 u, Vec3 v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

Vec3 vec3_cross(Vec3 u, Vec3 v) {
    return vec3(u.y * v.z - u.z * v.y,
                u.z * v.x - u.x * v.z,
                u.x * v.y - u.y * v.x);
}

float vec3_len_sq(Vec3 v) {
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

float vec3_len(Vec3 v) {
    return sqrt(vec3_len_sq(v));
}

void vec3_print(Vec3 v) {
    printf("%f %f %f\n", v.x, v.y, v.z);
}

Vec3 vec3_unit(Vec3 v) {
    return vec3_mult(v, 1 / vec3_len(v));
}

Vec3 vec3_lerp(Vec3 from, Vec3 to, float t) {
    return vec3_sum(vec3_mult(from, 1 - t), vec3_mult(to, t));
}

// Vec3 end

// Color start

Color color(float r, float g, float b) {
    Color o = {
        .x = r,
        .y = g,
        .z = b,
    };
    return o;
}

void color_write(Color *pixel_color) {
    float r = pixel_color->x;
    float g = pixel_color->y;
    float b = pixel_color->z;

    int ir = (int) 255.999 * r;
    int ig = (int) 255.999 * g;
    int ib = (int) 255.999 * b;

    printf("%i %i %i\n", ir, ig, ib);
}

// Color end

// Ray start

Point3 point3(float x, float y, float z) {
    Point3 o = {
        .x = x,
        .y = y,
        .z = z,
    };
    return o;
}

Ray ray(Point3 origin, Vec3 direction) {
    Ray r = {
        .origin = origin,
        .direction = direction,
    };
    return r;
}

Point3 ray_at(Ray r, float t) {
    return vec3_sum(r.origin, vec3_mult(r.direction, t));
}

// Ray end

#endif // RT_IMPLEMENTATION
