#include "math.h"

/* VECTOR 2 */
void m_vec2_print(vec2_t* src) {
    printf("vec2(%.2f, %.2f)\n", src->x, src->y);
}

vec2_t m_vec2_add(vec2_t a, vec2_t b) {
    return (vec2_t) {
        a.x + b.x,
        a.y + b.y
    };
}

vec2_t m_vec2_sub(vec2_t a, vec2_t b) {
    return (vec2_t) {
        a.x - b.x,
        a.y - b.y
    };
}

vec2_t m_vec2_div_scalar(vec2_t a, float scalar) {
    return (vec2_t) {
        a.x / scalar,
        a.y / scalar
    };
}

vec2_t m_vec2_mul_scalar(vec2_t a, float scalar) {
    return (vec2_t) {
        a.x * scalar,
        a.y * scalar
    };
}

float m_vec2_mag(vec2_t a) {
    return abs(sqrtf(powf(a.x, 2) + powf(a.y, 2)));
}

vec2_t m_vec2_norm(vec2_t a) {
    float length = m_vec2_mag(a);
    return (vec2_t) {
        a.x / length,
        a.y / length
    };
}

float m_vec2_dot(vec2_t a, vec2_t b) {
    return (a.x * b.x + a.y * b.y);
}

/* VECTOR 3 */
void m_vec3_print(vec3_t* src) {
    printf("vec3(%.2f, %.2f, %.2f)\n", src->x, src->y, src->z);
}

vec3_t m_vec3_zero(void) {
    return (vec3_t){ 0.0f, 0.0f, 0.0f };
}

vec3_t m_vec3_fill(float value) {
    return (vec3_t){ value, value, value };
}

vec3_t m_vec3_add(vec3_t a, vec3_t b) {
    return (vec3_t) {
        a.x + b.x,
        a.y + b.y,
        a.z + b.z
    };
}

vec3_t m_vec3_sub(vec3_t a, vec3_t b) {
    return (vec3_t) {
        a.x - b.x,
        a.y - b.y,
        a.z - b.z
    };
}

vec3_t m_vec3_div_scalar(vec3_t a, float scalar) {
    return (vec3_t) {
        a.x / scalar,
        a.y / scalar,
        a.z / scalar
    };
}

vec3_t m_vec3_mul_scalar(vec3_t a, float scalar) {
    return (vec3_t) {
        a.x * scalar,
        a.y * scalar,
        a.z * scalar
    };
}

float m_vec3_mag(vec3_t a) {
    return abs(sqrtf(powf(a.x, 2) + powf(a.y, 2) + powf(a.z, 2)));
}

vec3_t m_vec3_norm(vec3_t a) {
    float length = m_vec3_mag(a);
    return (vec3_t) {
        a.x / length,
        a.y / length,
        a.z / length
    };
}

float m_vec3_dot(vec3_t a, vec3_t b) {
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

vec3_t m_vec3_cross(vec3_t a, vec3_t b) {
    return (vec3_t) {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

vec3_t m_vec3_negate(vec3_t a) {
    return (vec3_t) {
        -a.x,
        -a.y,
        -a.z
    };
}

/* VECTOR 4 */
void m_vec4_print(vec4_t* src) {
    printf("vec4(%.2f, %.2f, %.2f, %.2f)\n", src->x, src->y, src->z, src->w);
}

vec4_t m_vec4_add(vec4_t a, vec4_t b) {
    return (vec4_t) {
        a.x + b.x,
        a.y + b.y,
        a.z + b.z,
        a.z + b.z
    };
}

vec4_t m_vec_sub(vec4_t a, vec4_t b) {
    return (vec4_t) {
        a.x - b.x,
        a.y - b.y,
        a.z - b.z,
        a.z - b.z
    };
}

vec4_t m_vec4_div_scalar(vec4_t a, float scalar) {
    return (vec4_t) {
        a.x / scalar,
        a.y / scalar,
        a.z / scalar,
        a.z / scalar
    };
}

vec4_t m_vec4_mul_scalar(vec4_t a, float scalar) {
    return (vec4_t) {
        a.x * scalar,
        a.y * scalar,
        a.z * scalar,
        a.z * scalar
    };
}

/* MATRIX 4x4 */
void m_mat4_print(mat4_t* src) {
    printf("Matrix4x4(%p)\n", src);

    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            printf("%.2f\t", src->v[col][row]);
        }
        printf("\n");
    }

    printf("\n\n");
}

mat4_t m_mat4_identity(void) {
    mat4_t m;

    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            m.v[col][row] = col == row ? 1.0f : 0.0f;
        }
    }

    return m;
}

mat4_t m_mat4_add(mat4_t a, mat4_t b) {
    mat4_t m;

    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            m.v[col][row] = a.v[col][row] + b.v[col][row];
        }
    }

    return m;
}

mat4_t m_mat4_sub(mat4_t a, mat4_t b) {
    mat4_t m;

    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            m.v[col][row] = a.v[col][row] - b.v[col][row];
        }
    }

    return m;
}

mat4_t m_mat4_mul_scalar(mat4_t a, float scalar) {
    mat4_t m;

    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            m.v[col][row] = a.v[col][row] * scalar;
        }
    }

    return m;
}

mat4_t m_mat4_mul(mat4_t a, mat4_t b) {
    mat4_t m;

    int k, r, c;
    for(c=0; c<4; ++c) {
        for(r=0; r<4; ++r) {
            m.v[c][r] = 0.f;
            for(k=0; k<4; ++k) {
                m.v[c][r] += a.v[k][r] * b.v[c][k];
            }
        }
    }

    return m;
}

/* MAT4x4 SPECIAL FUNCTIONS */
mat4_t m_rotate_x(float angle) {
    mat4_t m = m_mat4_identity();

    float s = sinf(angle);
    float c = cosf(angle);

    m.m11 = c;
    m.m12 = -s;
    
    m.m21 = s;
    m.m22 = c;

    return m;
}

mat4_t m_rotate_y(float angle) {
    mat4_t m = m_mat4_identity();

    m.m00 = cosf(angle);
    m.m02 = sinf(angle);

    m.m20 = -sinf(angle);
    m.m22 = cosf(angle);
    
    return m;
}

mat4_t m_rotate_z(float angle) {
    mat4_t m = m_mat4_identity();

    m.m00 = cosf(angle);
    m.m01 = -sinf(angle);

    m.m10 = sinf(angle);
    m.m11 = cosf(angle);

    return m;
}

mat4_t m_rotate(vec3_t rotation) {
    mat4_t m = m_mat4_identity();

    return m;
}

mat4_t m_scale(vec3_t scale) {
    mat4_t m = m_mat4_identity();

    m.m00 = scale.x;
    m.m11 = scale.y;
    m.m22 = scale.z;

    return m;
}

mat4_t m_translate(vec3_t position) {
    mat4_t m = m_mat4_identity();

    m.m03 = position.x;
    m.m13 = position.y;
    m.m23 = position.z;

    return m;
}

mat4_t m_projection(float fov, float aspect, float near, float far) {
    mat4_t m = m_mat4_identity();

    float range = tanf(fov / 2.0f) * near;
    float sx = (2 * near) / (range * aspect + range * aspect);
    float sy = near / range;
    float sz = -(far + near) / (far - near);
    float pz = -(2 * far * near) / (far - near);

    m.m00 = sx;
    m.m11 = sy;
    m.m22 = sz;
    m.m23 = pz;
    m.m32 = -1.0f;
    m.m33 =  0.0f;

    return m;
}

mat4_t m_lookat(vec3_t eye, vec3_t at, vec3_t up) {
    mat4_t m = m_mat4_identity();

    vec3_t zaxis = m_vec3_norm(m_vec3_sub(eye, at));
    vec3_t xaxis = m_vec3_norm(m_vec3_cross(zaxis, up));
    vec3_t yaxis = m_vec3_cross(xaxis, zaxis);

    m_vec3_negate(zaxis);

    m.v4[0] = (vec4_t) { xaxis.x, xaxis.y, xaxis.z, -m_vec3_dot(xaxis, eye) };
    m.v4[1] = (vec4_t) { yaxis.x, yaxis.y, yaxis.z, -m_vec3_dot(yaxis, eye) };
    m.v4[2] = (vec4_t) { zaxis.x, zaxis.y, zaxis.z, -m_vec3_dot(zaxis, eye) };
    m.v4[3] = (vec4_t) { 0, 0, 0, 1 };

    return m;
}

vec3_t m_normal_from_triangle(triangle_t triangle) {
    vec3_t surfaceNormal;

    vec3_t U = m_vec3_sub(triangle.points[1], triangle.points[0]);
    vec3_t V = m_vec3_sub(triangle.points[2], triangle.points[0]);

    surfaceNormal.x = (U.y * V.z) - (U.z * V.y);
    surfaceNormal.y = (U.z * V.x) - (U.x * V.z);
    surfaceNormal.z = (U.x * V.y) - (U.y * V.x);

    return surfaceNormal;
}

/* TRANSFORMATIONS */
transform_t m_transform_create(void) {
    return (transform_t) {
        m_vec3_zero(),
        m_vec3_zero(),
        m_vec3_fill(1.f),
        m_mat4_identity()
    };
}

void m_transform_update(transform_t* transform, float temp) {
    mat4_t t = m_translate(transform->position);

    mat4_t s = m_scale(transform->scale);

    transform->matrix = m_mat4_mul(t, s);
}
