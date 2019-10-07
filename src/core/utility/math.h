#ifndef M_MATH_H
#define M_MATH_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265

#define DEG2RAD (PI / 180)
#define RAD2DEG (180 / PI)

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

typedef struct {
    vec2_t p1;
    vec2_t p2;
} m_line_vec2_t;

typedef struct {
    vec3_t p1;
    vec3_t p2;
} m_line_vec3_t;

typedef union {
    float v[4][4];
    struct {
        float m00, m10, m20, m30;
        float m01, m11, m21, m31;
        float m02, m12, m22, m32;
        float m03, m13, m23, m33;
    };
} mat4_t;

// vec2
void m_vec2_print(vec2_t a);
vec2_t m_vec2_add(vec2_t a, vec2_t b);
vec2_t m_vec2_sub(vec2_t a, vec2_t b);
vec2_t m_vec2_div_scalar(vec2_t a, float scalar);
vec2_t m_vec2_mul_scalar(vec2_t a, float scalar);
vec2_t m_vec2_norm(vec2_t a);
float m_vec2_mag(vec2_t a);
float m_vec2_dot(vec2_t a, vec2_t b);
float m_vec2_cross(vec2_t a, vec2_t b);

// vec3


#endif // M_MATH_H
