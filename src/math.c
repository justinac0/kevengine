#include "math.h"

void m_vec3_print(vec3_t a) {
    printf("%f\t%f\t%f\n", a.x, a.y, a.z);
}

void m_mat4_fill(mat4_t *dest, float value) {
    int col, row;
    for (col = 0; col < 4; col++) {
        for (row = 0; row < 4; row++) {
            dest->v[col][row] = value;
        }
    }
}

void m_mat4_identity(mat4_t *dest) {
    int col, row;
    for (col = 0; col < 4; col++) {
        for (row = 0; row < 4; row++) {
            dest->v[col][row] = (col == row) ? 1 : 0;
        }
    }
}

void m_mat4_mul(mat4_t *dest, mat4_t a, mat4_t b) {
    mat4_t temp;
    int k, r, c;
    for (c = 0; c < 4; ++c) {
        for (r = 0; r < 4; ++r) {
            temp.v[c][r] = 0.0f;
            for (k = 0; k < 4; ++k) {
                temp.v[c][r] += a.v[k][r] * b.v[c][k];
            }
        }
    }

    *dest = temp;
}

vec3_t m_vec3_normalize(vec3_t a) {
    float len = sqrtf((a.x * a.x) + (a.y * a.y) + (a.z * a.z));

    vec3_t temp = {};
    temp.x = (a.x / len);
    temp.y = (a.y / len);
    temp.z = (a.z / len);

    return (temp);
}

vec3_t m_vec3_cross(vec3_t a, vec3_t b) {
    vec3_t temp = {};
    temp.x = a.y * b.z - a.z * b.y;
    temp.y = a.z * b.x - a.x * b.z;
    temp.z = a.x * b.y - a.y * b.x;

    return (temp);
}

vec3_t m_vec3_sub(vec3_t a, vec3_t b) {
    vec3_t temp = {};
    temp.x = a.x - b.x;
    temp.y = a.y - b.y;
    temp.z = a.z - b.z;

    return (temp);
}

vec3_t m_vec3_add(vec3_t a, vec3_t b) {
    vec3_t temp = {};
    temp.x = a.x + b.x;
    temp.y = a.y + b.y;
    temp.z = a.z + b.z;

    return (temp);
}

vec3_t m_vec3_mul_scalar(vec3_t a, float b) {
    vec3_t temp = {};
    temp.x = a.x * b;
    temp.y = a.y * b;
    temp.z = a.z * b;

    return (temp);
}

void m_mat4_row(vec4_t r, mat4_t m, int i) {
    for (int k = 0; k < 4; ++k) {
        r.v[k] = m.v[k][i];
    }
}

void m_mat4_col(vec4_t r, mat4_t m, int i) {
    for (int k = 0; k < 4; ++k) {
        r.v[k] = m.v[i][k];
    }
}

float m_vec4_mul_inner(vec4_t a, vec4_t b) {
    float p = 0.0f;
    p += a.x * b.x;
    p += a.y * b.y;
    p += a.z * b.z;

    return (p);
}

void m_mat4_translate_in_place(mat4_t *dest, float x, float y, float z) {
    for (int r = 0; r < 4; r++) {
        dest->v[3][r] = dest->v[0][r] * x + dest->v[1][r] * y + dest->v[2][r] * z;
    }
}

void m_mat4_print(mat4_t *src) {
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            printf("%d%d : %f\t ", col, row, src->v[col][row]);
        }
        printf("\n");
    }
    printf("\n");
}

void m_translate(mat4_t* dest, float x, float y, float z) {
    m_mat4_identity(dest);
    dest->m03 = x;
    dest->m13 = y;
    dest->m23 = z;
}

void m_rotate_x(mat4_t* dest, float angle) {
    m_mat4_identity(dest);
    dest->m11 =  cosf(angle * DEG2RAD);
    dest->m12 = -sinf(angle * DEG2RAD);
    dest->m21 =  sinf(angle * DEG2RAD);
    dest->m22 =  cosf(angle * DEG2RAD);
}

void m_rotate_y(mat4_t* dest, float angle) {
    m_mat4_identity(dest);
    dest->m00 =  cosf(angle * DEG2RAD);
    dest->m02 =  sinf(angle * DEG2RAD);
    dest->m20 = -sinf(angle * DEG2RAD);
    dest->m22 =  cosf(angle * DEG2RAD);
}

void m_rotate_z(mat4_t* dest, float angle) {
    m_mat4_identity(dest);
    dest->m00 =  cosf(angle * DEG2RAD);
    dest->m01 = -sinf(angle * DEG2RAD);
    dest->m10 =  sinf(angle * DEG2RAD);
    dest->m11 =  cosf(angle * DEG2RAD);
}

void m_perspective(mat4_t *dest, float fov, float aspect, float znear, float zfar) {
    double range = 1.0f / tanf(fov / 2.0f);

    dest->v[0][0] = range / aspect;
    dest->v[0][1] = 0.0f;
    dest->v[0][2] = 0.0f;
    dest->v[0][3] = 0.0f;

    dest->v[1][0] = 0.0f;
    dest->v[1][1] = range;
    dest->v[1][2] = 0.0f;
    dest->v[1][3] = 0.0f;

    dest->v[2][0] = 0.0f;
    dest->v[2][1] = 0.0f;
    dest->v[2][2] = -((zfar + znear) / (zfar - znear));
    dest->v[2][3] = -1.0f;

    dest->v[3][0] = 0.0f;
    dest->v[3][1] = 0.0f;
    dest->v[3][2] = -((2.0f * zfar * znear) / (zfar - znear));
    dest->v[3][3] = 1.0f;
}

void m_orthographic(mat4_t *dest, float left, float right, float top, float bottom, float znear, float zfar) {
    dest->v[0][0] = 2.f / (right - left);
    dest->v[0][1] = dest->v[0][2] = dest->v[0][3] = 0.f;

    dest->v[1][1] = 2.f / (top - bottom);
    dest->v[1][0] = dest->v[1][2] = dest->v[1][3] = 0.f;

    dest->v[2][2] = -2.f / (zfar - znear);
    dest->v[2][0] = dest->v[2][1] = dest->v[2][3] = 0.f;

    dest->v[3][0] = -(right + left) / (right - left);
    dest->v[3][1] = -(top + bottom) / (top - bottom);
    dest->v[3][2] = -(zfar + znear) / (zfar - znear);
    dest->v[3][3] = 1.f;
}

void m_look_at(mat4_t *dest, vec3_t eye, vec3_t target, vec3_t up) {
    vec3_t f, s, t;
    f = m_vec3_sub(target, eye);
    f = m_vec3_normalize(f);

    s = m_vec3_cross(f, up);
    s = m_vec3_normalize(s);

    t = m_vec3_cross(s, f);

    dest->v[0][0] = s.x;
    dest->v[0][1] = t.x;
    dest->v[0][2] =-f.x;
    dest->v[0][3] = 0.0f;

    dest->v[1][0] = s.y;
    dest->v[1][1] = t.y;
    dest->v[1][2] =-f.y;
    dest->v[1][3] = 0.0f;

    dest->v[2][0] = s.z;
    dest->v[2][1] = t.z;
    dest->v[2][2] =-f.z;
    dest->v[2][3] = 0.0f;

    dest->v[3][0] = 0.0f;
    dest->v[3][1] = 0.0f;
    dest->v[3][2] = 0.0f;
    dest->v[3][3] = 1.0f;

    m_mat4_translate_in_place(dest, -eye.x, -eye.y, -eye.z);
}
