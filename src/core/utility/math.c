#include "math.h"

void m_vec2_print(vec2_t a) {
    printf("vec2(%.2f, %.2f)\n", a.x, a.y);
}

vec2_t m_vec2_add(vec2_t a, vec2_t b) {
    return (vec2_t){ a.x + b.x, a.y + b.y };
}

vec2_t m_vec2_sub(vec2_t a, vec2_t b) {
    return (vec2_t){ a.x - b.x, a.y - b.y };
}

vec2_t m_vec2_div_scalar(vec2_t a, float scalar) {
    return (vec2_t){ a.x / scalar, a.y / scalar };
}

vec2_t m_vec2_mul_scalar(vec2_t a, float scalar) {
    return (vec2_t){ a.x * scalar, a.y * scalar };
}

vec2_t m_vec2_norm(vec2_t a) {
    float length = m_vec2_mag(a);
    return (vec2_t){ a.x / length, a.y / length };
}

float m_vec2_mag(vec2_t a) {
    return abs(sqrtf(powf(a.x, 2) + powf(a.y, 2)));
}

float m_vec2_dot(vec2_t a, vec2_t b) {

}

float m_vec2_cross(vec2_t a, vec2_t b) {

}
