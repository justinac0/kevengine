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

typedef union {
    float v[4][4];
    struct {
        float m00, m10, m20, m30;
        float m01, m11, m21, m31;
        float m02, m12, m22, m32;
        float m03, m13, m23, m33;
    };
} mat4_t;

vec2_t m_vec2_add(vec2_t a, vec2_t b);
vec2_t m_vec2_sub(vec2_t a, vec2_t b);

void m_vec3_print(vec3_t a);
vec3_t m_vec3_normalize(vec3_t a);
vec3_t m_vec3_cross(vec3_t a, vec3_t b);
vec3_t m_vec3_sub(vec3_t a, vec3_t b);
vec3_t m_vec3_add(vec3_t a, vec3_t b);
vec3_t m_vec3_mul_scalar(vec3_t a, float b);
void m_mat4_row(vec4_t r, mat4_t m, int i);
void m_mat4_col(vec4_t r, mat4_t m, int i);
float m_vec4_mul_inner(vec4_t a, vec4_t b);
void m_mat4_translate_in_place(mat4_t *dest, float x, float y, float z);
void m_mat4_print(mat4_t *src);
void m_mat4_fill(mat4_t *dest, float value);
void m_mat4_identity(mat4_t *dest);
void m_mat4_mul(mat4_t *dest, mat4_t a, mat4_t b);
void m_translate(mat4_t* dest, float x, float y, float z);
void m_rotate_x(mat4_t* dest, float angle);
void m_rotate_y(mat4_t* dest, float angle);
void m_rotate_z(mat4_t* dest, float angle);
void m_scale(mat4_t* dest, vec3_t xyz);
void m_perspective(mat4_t *dest, float fov, float aspect, float znear, float zfar);
void m_orthographic(mat4_t *dest, float left, float right, float top, float bottom, float znear, float zfar);
void m_look_at(mat4_t *dest, vec3_t eye, vec3_t target, vec3_t up);

#endif // M_MATH_H