#ifndef G_MATH_H
#define G_MATH_H

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

// VEC2 /////////////////////////////////////////////////////////
static inline vec2_t vec2_zero(void) {
    return (vec2_t){ 0, 0 };
}

static inline vec2_t vec2_fill(float value) {
    return (vec2_t){ value, value };
}

static inline vec2_t vec2_add(vec2_t* a, vec2_t* b) {
    vec2_t result;
    result.x = a->x + b->x;
    result.y = a->y + b->y;

    return result;
}

static inline vec2_t vec2_sub(vec2_t* a, vec2_t* b) {
    vec2_t result;    
    result.x = a->x - b->x;
    result.y = a->y - b->y;

    return result;
}

static inline vec2_t vec2_div_scalar(vec2_t* src, float scalar) {
    vec2_t result;
    result.x = src->x / scalar; 
    result.y = src->y / scalar; 

    return result;
}

static inline float vec2_dot(vec2_t* a, vec2_t* b) {
    return (a->x * b->x + a->y * b->y);
}

static inline float vec2_cross(vec2_t* a, vec2_t* b) {
    return (a->x * b->y - a->y * b->x);
}

static inline float vec2_mag(vec2_t* src) {
    return (sqrtf(powf(src->x, 2) + powf(src->y, 2)));
}

static inline vec2_t vec2_scalar(vec2_t* src, float scalar) {
    vec2_t result;
    result.x = src->x * scalar;
    result.y = src->y * scalar;

    return result;
}

static inline vec2_t vec2_norm(vec2_t* src) {
     vec2_t result;
     result = vec2_div_scalar(src, abs(vec2_mag(src)));

    return result;
}

// VEC3 /////////////////////////////////////////////////////////
static inline vec3_t vec3_zero(void) {
    return (vec3_t){ 0, 0, 0 };
}

static inline vec3_t vec3_fill(float value) {
    return (vec3_t){ value, value, value };
}

static inline vec3_t vec3_add(vec3_t* a, vec3_t* b) {
    vec3_t result;
    result.x = a->x + b->x;
    result.y = a->y + b->y;
    result.z = a->z + b->z;

    return result;
}

static inline vec3_t vec3_sub(vec3_t* a, vec3_t* b) {
    vec3_t result;
    result.x = a->x - b->x;
    result.y = a->y - b->y;
    result.z = a->z - b->z;

    return result;
}

static inline vec3_t vec3_div_scalar(vec3_t* src, float scalar) {
    vec3_t result;
    result.x = src->x / scalar;
    result.y = src->y / scalar;
    result.z = src->z / scalar;

    return result;
}

static inline float vec3_dot(vec3_t* a, vec3_t* b) {
    return (a->x * b->x + a->y * b->y + a->z * b->z);
}

static inline float vec3_cross(vec3_t* a, vec3_t* b) {
    return (a->x * b->y - a->y * b->x - a->z * b->z);
}

static inline float vec3_mag(vec3_t* src) {
    return (sqrtf(powf(src->x, 2) + powf(src->y, 2) + powf(src->z, 2)));
}

static inline vec3_t vec3_scalar(vec3_t* src, float scalar) {
    vec3_t result;
    result.x = src->x * scalar;
    result.y = src->y * scalar;
    result.z = src->z * scalar;

    return result;
}

static inline vec3_t vec3_norm(vec3_t* src) {
     vec3_t result;
     result = vec3_div_scalar(src, abs(vec3_mag(src)));

    return result;
}

// MAT4 /////////////////////////////////////////////////////////
static inline void mat4_print(mat4_t* src) {
    printf("mat4_t: addr(%p)\n", src);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%.2f\t", src->v[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}

static inline mat4_t mat4_identity(void) {
    mat4_t result;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j) {
                result.v[i][j] = 1.f;
            } else {
                result.v[i][j] = 0.f;
            }
        }
    }

    return result;
}

static inline mat4_t mat4_add(mat4_t* a, mat4_t* b) {
    mat4_t result;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.v[i][j] = a->v[i][j] + b->v[i][j];
        }
    }

    return result;
}

static inline mat4_t mat4_sub(mat4_t* a, mat4_t* b) {
    mat4_t result;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.v[i][j] = a->v[i][j] - b->v[i][j];
        }
    }

    return result;
}

static inline mat4_t mat4_mul(mat4_t* a, mat4_t* b) {
    mat4_t result;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.v[i][j] = a->v[i][j] * b->v[j][i];
        }
    }

    return result;
}

static inline mat4_t mat4_translate(vec3_t position) {
    mat4_t result;

    return result;
}

static inline mat4_t mat4_transpose() {
    mat4_t result;

    

    return result;
}

#endif // G_MATH_H