#include "math.h"

void m_vec2_add(vec2_t* dest, vec2_t a, vec2_t b) {
    dest->x = a.x + b.x;
    dest->y = a.y + b.y;
}

void m_vec2_sub(vec2_t* dest, vec2_t a, vec2_t b) {
    dest->x = a.x - b.x;
    dest->y = a.y - b.y;
}

void m_mat4_print(mat4_t* src) {
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            printf("%f ", src->array[col][row]);
        }
        printf("\n");
    }
    printf("\n");
}

void m_mat4_identity(mat4_t* dest) {
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            dest->array[col][row] = col == row ? 1.0f : 0.0f;
        }
    }
}

void m_mat4_add(mat4_t* dest, mat4_t* a, mat4_t* b) {
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            dest->array[col][row] = a->array[col][row] + b->array[col][row];
        }
    }
}

void m_mat4_sub(mat4_t* dest, mat4_t* a, mat4_t* b) {
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            dest->array[col][row] = a->array[col][row] - b->array[col][row];
        }
    }
}

void m_mat4_mul(mat4_t* dest, mat4_t* a, mat4_t* b) {
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            dest->array[col][row] = a->array[col][row] * b->array[row][col];
        }
    }
}

void m_mat4_mul_scalar(mat4_t* dest, float scalar) {
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            dest->array[col][row] *= scalar;
        }
    }
}

void m_perspective(mat4_t* dest, float fov, float aspect, float znear, float zfar) {
    float a = 1.0f / tanf(fov / 2.0f);

    dest->m00 = a / aspect;
    dest->m01 = 0.0f;
    dest->m02 = 0.0f;
    dest->m03 = 0.0f;

    dest->m10 = 0.0f;
    dest->m11 = a;
    dest->m12 = 0.0f;
    dest->m13 = 0.0f;

    dest->m20 = 0.0f;
    dest->m21 = 0.0f;
    dest->m22 = -((zfar + znear) / (zfar - znear));
    dest->m23 = -1.0f;

    dest->m30 = 0.0f;
    dest->m31 = 0.0f;
    dest->m32 = -((2.0f * zfar * znear) / (zfar - znear));
    dest->m33 = 0.0f;
}

void m_look_at(mat4_t* dest, vec3_t eye, vec3_t forward, vec3_t up) {

}
