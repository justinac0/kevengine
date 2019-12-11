#include "camera.h"

double oldX, oldY;
double newX, newY;
float x, y, z;

mat4_t mX;
mat4_t mY;
mat4_t mZ;

mat4_t translation;
mat4_t rotation;

camera_t camera_create() {
    camera_t camera;
    camera.yaw      = 0;
    camera.pitch    = 0;
    camera.roll     = 0;
    camera.matrix   = m_mat4_identity();

    mX = m_mat4_identity();
    mY = m_mat4_identity();
    mZ = m_mat4_identity();

    translation = m_mat4_identity();
    rotation    = m_mat4_identity();

    return camera;
}

void camera_drag_look(camera_t* camera) {
    float speed = 0.5f;
 
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS) {
        camera->matrix.m03 += camera->matrix.m02;
        camera->matrix.m13 += camera->matrix.m12;
        camera->matrix.m23 += camera->matrix.m22;
    }

    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS) {
        camera->matrix.m03 -= camera->matrix.m02;
        camera->matrix.m13 -= camera->matrix.m12;
        camera->matrix.m23 -= camera->matrix.m22;
    }

    //camera->matrix = m_mat4_mul(camera->matrix, m_translate((vec3_t){ x, y, z }));
    //camera->matrix = m_mat4_mul(camera->matrix, mX);
    //camera->matrix = m_mat4_mul(camera->matrix, mY);
    //camera->matrix = m_mat4_mul(camera->matrix, mZ);

    if (!glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        glfwGetCursorPos(glfwGetCurrentContext(), &oldX, &oldY);
        return;
    }

    glfwGetCursorPos(glfwGetCurrentContext(), &newX, &newY);
    vec2_t mouseDiff = (vec2_t){ oldX - newX, oldY - newY};

    float x = cosf(camera->pitch) * cosf(camera->yaw);
    float y = sinf(camera->pitch);
    float z = cosf(camera->pitch) * sinf(camera->yaw);

    // cos(yaw)cos(pitch) -cos(yaw)sin(pitch)sin(roll)-sin(yaw)cos(roll) -cos(yaw)sin(pitch)cos(roll)+sin(yaw)sin(roll)
    // sin(yaw)cos(pitch) -sin(yaw)sin(pitch)sin(roll)+cos(yaw)cos(roll) -sin(yaw)sin(pitch)cos(roll)-cos(yaw)sin(roll)
    // sin(pitch)          cos(pitch)sin(roll)                            cos(pitch)sin(roll)

    // camera->matrix.m00 = cosf(camera->pitch) * cosf(camera->yaw);
    // camera->matrix.m02 = sinf(camera->pitch);
    // camera->matrix.m01 = cosf(camera->pitch) * sinf(camera->yaw);

    // camera->matrix.m10 = cosf(camera->pitch) * cosf(camera->yaw);
    // camera->matrix.m11 = sinf(camera->pitch);
    // camera->matrix.m12 = cosf(camera->pitch) * sinf(camera->yaw);

    // float angle = camera->pitch;

    // camera->matrix.m11 = cosf(angle);
    // camera->matrix.m12 = -sinf(angle);
    
    // camera->matrix.m21 = sinf(angle);
    // camera->matrix.m22 = cosf(angle);

    // angle = camera->yaw;

    // camera->matrix.m00 = cosf(angle);
    // camera->matrix.m02 = sinf(angle);

    // camera->matrix.m20 = -sinf(angle);
    // camera->matrix.m22 = cosf(angle);

    // angle = camera->roll;

    // camera->matrix.m00 = cosf(angle);
    // camera->matrix.m01 = -sinf(angle);
    
    // camera->matrix.m10 = sinf(angle);
    // camera->matrix.m11 = cosf(angle);

    float sens = 0.0001f;
    camera->yaw   += mouseDiff.x * sens;
    camera->pitch += mouseDiff.y * sens;
}
