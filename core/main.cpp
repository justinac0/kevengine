#include "kevin.hpp"
#include <thread>
#include <Eigen/Core>

using namespace kevin;

const uint32_t WINDOW_WIDTH  = 1280;
const uint32_t WINDOW_HEIGHT = 720;

std::vector<float> vertices = {
    -1, -1, 0,
     1, -1, 0,
     0,  1, 0
};

std::vector<float> colours = {
    1.0, 0.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 0.0, 1.0
};

std::vector<int> indices = {
    0, 1, 2
};

// remove later nerd
inline Eigen::Matrix4f ProjectionMatrix(float fov, float aspect, float znear, float zfar) {
    float range = atan(fov / 2.0f) * znear;
    float sx    = (2.0f * znear) / (range * aspect + range * aspect);
    float sy    = znear / range;
    float sz    = -(zfar + znear) / (zfar - znear);
    float pz    = -(2.0f * zfar * znear) / (zfar - znear);

    Eigen::Matrix4f perspective;
    perspective << sx,    0.0f,  0.0f, 0.0f,
                   0.0f,  sy,    0.0f, 0.0f,
                   0.0f,  0.0f,  sz,   pz,
                   0.0f,  0.0f, -1.0f, 0.0f;

    return perspective;
}

void SceneRender(world::Scene* scene, renderer::ShaderProgram shaderProgram, world::Camera& camera) {
    if (scene == nullptr) return;

    for (int i = 0; i < (int) scene->objects.size(); i++) {
        camera.Update();
        glUseProgram(shaderProgram.GetID());
        glUniform3f(glGetUniformLocation(shaderProgram.GetID(), "m_light_pos"), (*scene).objects.at(0).GetTransform().position(0),
                                                                                (*scene).objects.at(0).GetTransform().position(1),
                                                                                (*scene).objects.at(0).GetTransform().position(2));

        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.GetID(), "m_projection"), 1, GL_FALSE, &camera.GetProjectionMatrix()(0));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.GetID(), "m_view"), 1, GL_FALSE, &camera.GetViewMatrix()(0));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.GetID(), "m_transform"), 1, GL_FALSE, &(*scene).objects.at(i).GetTransform().GetMatrix()(0));

        (*scene).objects.at(i).UpdateModel();
        (*scene).objects.at(i).RenderModel();
    }
}

int main() {
    renderer::Renderer renderer = renderer::Renderer(WINDOW_WIDTH, WINDOW_HEIGHT);

    renderer::Shader vertexShader = renderer::Shader("build/vertex.glsl", GL_VERTEX_SHADER);
    renderer::Shader fragmentShader = renderer::Shader("build/fragment.glsl", GL_FRAGMENT_SHADER);
    renderer::ShaderProgram shaderProgram = renderer::ShaderProgram(vertexShader, fragmentShader);

    world::Camera camera(1.0f, 0.05f);
    world::Scene scene("./build/file.znk");

    while (!renderer.GetWindowShouldClose()) {
        renderer.UpdateWindow();

        scene.objects.at(0).Move(cosf(glfwGetTime()) * 5, 20, sinf(glfwGetTime())*5);
 
        scene.objects.at(7).Move(scene.objects.at(7).GetTransform().position(0), sinf(glfwGetTime())/5 + 1.5, scene.objects.at(7).GetTransform().position(2));

        SceneRender(&scene, shaderProgram, camera);
    }

    return 0;
}
