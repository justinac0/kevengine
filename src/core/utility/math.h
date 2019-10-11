#ifndef M_MATH_H
#define M_MATH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
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
    struct {
        vec4_t v4[4];
    };
} mat4_t;

typedef struct {
    vec3_t points[3];
} triangle_t;

/* VECTOR 2 */
void m_vec2_print(vec2_t* src);
vec2_t m_vec2_add(vec2_t a, vec2_t b);
vec2_t m_vec2_sub(vec2_t a, vec2_t b);
vec2_t m_vec2_div_scalar(vec2_t a, float scalar);
vec2_t m_vec2_mul_scalar(vec2_t a, float scalar);
float m_vec2_mag(vec2_t a);
vec2_t m_vec2_norm(vec2_t a);
float m_vec2_dot(vec2_t a, vec2_t b);

/* VECTOR 3 */
void m_vec3_print(vec3_t* src);
vec3_t m_vec3_zero(void);
vec3_t m_vec3_fill(float value);
vec3_t m_vec3_add(vec3_t a, vec3_t b);
vec3_t m_vec3_sub(vec3_t a, vec3_t b);
vec3_t m_vec3_div_scalar(vec3_t a, float scalar);
vec3_t m_vec3_mul_scalar(vec3_t a, float scalar);
float m_vec3_mag(vec3_t a);
vec3_t m_vec3_norm(vec3_t a);
float m_vec3_dot(vec3_t a, vec3_t b);
vec3_t m_vec3_cross(vec3_t a, vec3_t b);
vec3_t m_vec3_mul_cross(vec3_t a, vec3_t b);
vec3_t m_vec3_negate(vec3_t a);

/* VECTOR 4 */
void m_vec4_print(vec4_t* src);
vec4_t m_vec4_add(vec4_t a, vec4_t b);
vec4_t m_vec_sub(vec4_t a, vec4_t b);
vec4_t m_vec4_div_scalar(vec4_t a, float scalar);
vec4_t m_vec4_mul_scalar(vec4_t a, float scalar);
float m_vec4_mul_inner(vec4_t a, vec4_t b);

/* MATRIX 4x4 */ // col major
void m_mat4_print(mat4_t* src);
mat4_t m_mat4_identity(void);
mat4_t m_mat4_add(mat4_t a, mat4_t b);
mat4_t m_mat4_mul_scalar(mat4_t a, float scalar);
mat4_t m_mat4_mul(mat4_t a, mat4_t b);
vec4_t m_mat4_row(mat4_t a, uint32_t row);
mat4_t m_mat4_translate_in_place(float x, float y, float z);

/* MAT4x4 SPECIAL FUNCTIONS */
mat4_t m_rotate_x(float angle);
mat4_t m_rotate_y(float angle);
mat4_t m_rotate_z(float angle);
mat4_t m_rotate(vec3_t rotation);
mat4_t m_scale(vec3_t scale);
mat4_t m_translate(vec3_t position);
mat4_t m_projection(float fov, float aspect, float near, float far);
mat4_t m_lookat(vec3_t eye, vec3_t at, vec3_t up);
vec3_t m_normal_from_triangle(triangle_t triangle);

#endif // M_MATH_H
