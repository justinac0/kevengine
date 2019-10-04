#ifndef MATH_H
#define MATH_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265

#define DEG2RAD (PI / 180)
#define RAD2DEG (180 / PI)

typedef union {
    float array[2];
    struct {
        float x;
        float y;
    };
} vec2_t;

typedef union {
    float array[3];
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
    float array[4];
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
    float array[4][4];
    struct {
        float m00, m10, m20, m30;
        float m01, m11, m21, m31;
        float m02, m12, m22, m32;
        float m03, m13, m23, m33;
    };
} mat4_t;

// vec2
void m_vec2_add(vec2_t* dest, vec2_t a, vec2_t b);
void m_vec2_sub(vec2_t* dest, vec2_t a, vec2_t b);

// vec3

// vec4

// mat4
void m_mat4_print(mat4_t* src);
void m_mat4_identity(mat4_t* dest);
void m_mat4_add(mat4_t* dest, mat4_t* a, mat4_t* b);
void m_mat4_sub(mat4_t* dest, mat4_t* a, mat4_t* b);
void m_mat4_mul(mat4_t* dest, mat4_t* a, mat4_t* b);
void m_mat4_mul_scalar(mat4_t* dest, float scalar);

void m_translate();
void m_rotate();
void m_scale();

void m_perspective(mat4_t* dest, float fov, float aspect, float znear, float zfar);
void m_look_at(mat4_t* dest, vec3_t eye, vec3_t forward, vec3_t up);

#endif // MATH_H
