#ifndef TINY_MATH_H
#define TINY_MATH_H

#include <math.h>

#define PI 3.14159265

#define DEG2RAD (PI / 180)
#define RAD2DEG (180 / PI)

#include <math.h>

typedef union {
    float v[2];
    struct {
        float x;
        float y;
    };
} vec2_t;

typedef union {
    float v[3];
    struct {
        float x;
        float y;
        float z;
    };
    struct {
        float r;
        float g;
        float b;
    };
} vec3_t;

typedef union {
    float v[4];
    struct {
        float x;
        float y;
        float z;
        float w;
    };
    struct {
        float r;
        float g;
        float b;
        float a;
    };
} vec4_t;

typedef union {
    float m[4][4];
    struct {
        float m00, m10, m20, m30;
        float m01, m11, m21, m31;
        float m02, m12, m22, m32;
        float m03, m13, m23, m33;
    };
} mat4_t;

static inline void vec2_add(vec2_t* dest, vec2_t* a, vec2_t* b) {
    dest->x = a->x + b->x;
    dest->y = a->y + b->y;
}

static inline void vec2_sub(vec2_t* dest, vec2_t* a, vec2_t* b) {
    dest->x = a->x - b->x;
    dest->y = a->y - b->y;
}

static inline void vec2_dot(float dest, vec2_t* a, vec2_t* b) {
    dest = a->x * b->x + a->y * b->y;
}

static inline void vec2_cross(float dest, vec2_t* a, vec2_t* b) {
    dest = a->x * b->y - a->y * b->x;
}

static inline void vec2_mag(float dest, vec2_t* src) {
    dest = sqrtf(powf(src->x, 2) + powf(src->y, 2));
}

static inline void vec2_scalar(vec2_t* dest, vec2_t* a, float scalar) {
    dest->x = a->x * scalar;
    dest->y = a->y * scalar;
}

#endif // TINY_MATH_H
