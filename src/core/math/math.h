#ifndef MATH_H
#define MATH_H

#include <stdio.h>
#include <math.h>

#define PI 3.14159265

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

static inline void vec3_print(vec3_t a) {
    printf("%f\t%f\t%f\n", a.x, a.y, a.z);
}

static inline float deg_to_rad(float deg) {
    return (deg * (PI/180));
}

static inline float rad_to_deg(float rad) {
    return (rad * (180/PI));
}

static inline void mat4_fill(mat4_t *dest, float value) {
    int col, row;
    for (col = 0; col < 4; col++) {
        for (row = 0; row < 4; row++) {
            dest->m[col][row] = value;
        }
    }
}

static inline void mat4_copy(mat4_t *dest, mat4_t src) {
    *dest = src;
}

static inline void mat4_identity(mat4_t *dest) {
    int col, row;
    for (col = 0; col < 4; col++) {
        for (row = 0; row < 4; row++) {
            dest->m[col][row] = (col == row) ? 1 : 0;
        }
    }
}

static inline void mat4_mul(mat4_t *dest, mat4_t a, mat4_t b) {
    mat4_t temp;
    int k, r, c;
    for (c = 0; c < 4; ++c) {
        for (r = 0; r < 4; ++r) {
            temp.m[c][r] = 0.0f;
            for (k = 0; k < 4; ++k) {
                temp.m[c][r] += a.m[k][r] * b.m[c][k];
            }
        }
    }

    mat4_copy(dest, temp);
}

static inline void mat4_translate(mat4_t *dest, vec3_t v) {
    dest->m[3][0] = v.x;
    dest->m[3][1] = v.y;
    dest->m[3][2] = v.z;
    dest->m[3][3] = 1;
}

static inline void mat4_scale(mat4_t *dest, vec3_t v) {
    dest->m[0][0] = v.x;
    dest->m[1][1] = v.y;
    dest->m[2][2] = v.z;
    dest->m[3][3] = 1;
}

static inline void mat4_rotate(mat4_t *dest, float angle) {
    dest->m[0][0] = cos(angle);
    dest->m[0][2] = sin(angle);
    dest->m[2][0] = -sin(angle);
    dest->m[2][2] = cos(angle);
}

static inline void mat4_projection(mat4_t *dest, float fov, float aspect, float znear, float zfar) {
    const double range = 1.0f / tanf(fov / 2.0f);

    dest->m[0][0] = range / aspect;
    dest->m[0][1] = 0.0f;
    dest->m[0][2] = 0.0f;
    dest->m[0][3] = 0.0f;

    dest->m[1][0] = 0.0f;
    dest->m[1][1] = range;
    dest->m[1][2] = 0.0f;
    dest->m[1][3] = 0.0f;

    dest->m[2][0] = 0.0f;
    dest->m[2][1] = 0.0f;
    dest->m[2][2] = -((zfar + znear) / (zfar - znear));
    dest->m[2][3] = -1.0f;

    dest->m[3][0] = 0.0f;
    dest->m[3][1] = 0.0f;
    dest->m[3][2] = -((2.0f * zfar * znear) / (zfar - znear));
    dest->m[3][3] = 0.0f;
}

static inline void mat4_orthographic(mat4_t *dest, float left, float right, float top, float bottom, float znear, float zfar) {
    dest->m[0][0] = 2.f / (right - left);
    dest->m[0][1] = dest->m[0][2] = dest->m[0][3] = 0.f;

    dest->m[1][1] = 2.f / (top - bottom);
    dest->m[1][0] = dest->m[1][2] = dest->m[1][3] = 0.f;

    dest->m[2][2] = -2.f / (zfar - znear);
    dest->m[2][0] = dest->m[2][1] = dest->m[2][3] = 0.f;

    dest->m[3][0] = -(right + left) / (right - left);
    dest->m[3][1] = -(top + bottom) / (top - bottom);
    dest->m[3][2] = -(zfar + znear) / (zfar - znear);
    dest->m[3][3] = 1.f;
}

static inline vec3_t vec3_normalize(vec3_t a) {
    float len = sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z));

    vec3_t temp = {};
    temp.x = (a.x / len);
    temp.y = (a.y / len);
    temp.z = (a.z / len);

    return (temp);
}

static inline vec3_t vec3_cross(vec3_t a, vec3_t b) {
    vec3_t temp = {};
    temp.x = a.y * b.z - a.z * b.y;
    temp.y = a.z * b.x - a.x * b.z;
    temp.z = a.x * b.y - a.y * b.x;

    return (temp);
}

static inline vec3_t vec3_sub(vec3_t a, vec3_t b) {
    vec3_t temp = {};
    temp.x = a.x - b.x;
    temp.y = a.y - b.y;
    temp.z = a.z - b.z;

    return (temp);
}

static inline vec3_t vec3_add(vec3_t a, vec3_t b) {
    vec3_t temp = {};
    temp.x = a.x + b.x;
    temp.y = a.y + b.y;
    temp.z = a.z + b.z;

    return (temp);
}

static inline vec3_t vec3_mul_scalar(vec3_t a, float b) {
    vec3_t temp = {};
    temp.x = a.x * b;
    temp.y = a.y * b;
    temp.z = a.z * b;

    return (temp);
}

static inline void mat4_row(vec4_t r, mat4_t m, int i) {
    for (int k = 0; k < 4; ++k) {
        r.v[k] = m.m[k][i];
    }
}

static inline void mat4_col(vec4_t r, mat4_t m, int i) {
    for (int k = 0; k < 4; ++k) {
        r.v[k] = m.m[i][k];
    }
}

static inline float vec4_mul_inner(vec4_t a, vec4_t b) {
    float p = 0.0f;
    p += a.x * b.x;
    p += a.y * b.y;
    p += a.z * b.z;

    return (p);
}

static inline void mat4_translate_in_place(mat4_t *dest, float x, float y, float z) {
    for (int r = 0; r < 4; r++) {
        dest->m[3][r] = dest->m[0][r] * x + dest->m[1][r] * y + dest->m[2][r] * z;
    }
}

static inline void mat4_print(mat4_t *src) {
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            printf("%d%d : %f\t ", col, row, src->m[col][row]);
        }
        printf("\n");
    }
    printf("\n");
}

static inline void mat4_look_at(mat4_t *dest, vec3_t eye, vec3_t target, vec3_t up) {
    vec3_t f, s, t;
    f = vec3_sub(target, eye);
    f = vec3_normalize(f);

    s = vec3_cross(f, up);
    s = vec3_normalize(s);

    t = vec3_cross(s, f);

    dest->m[0][0] = s.x;
    dest->m[0][1] = t.x;
    dest->m[0][2] =-f.x;
    dest->m[0][3] = 0.0f;

    dest->m[1][0] = s.y;
    dest->m[1][1] = t.y;
    dest->m[1][2] =-f.y;
    dest->m[1][3] = 0.0f;

    dest->m[2][0] = s.z;
    dest->m[2][1] = t.z;
    dest->m[2][2] =-f.z;
    dest->m[2][3] = 0.0f;

    dest->m[3][0] = 0.0f;
    dest->m[3][1] = 0.0f;
    dest->m[3][2] = 0.0f;
    dest->m[3][3] = 1.0f;

    mat4_translate_in_place(dest, -eye.x, -eye.y, -eye.z);
}

#endif // MATH_H