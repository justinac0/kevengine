#include "kevin.h"

#define FPS 120

int main(int argc, char* argv) {
    GLFWwindow* pWindow = window_create(640, 480, "kevin");

    GLuint shaderProgramID, lightShaderProgramID;
    mat4_t projection, view;

    shaderProgramID         = ogl_shader_load("bin/shaders/vertex.glsl", "bin/shaders/fragment.glsl");
    lightShaderProgramID    = ogl_shader_load("bin/shaders/vs_light.glsl", "bin/shaders/fs_light.glsl");

    memory_pool_t mp = u_memory_pool_create(1024);                                          

    model_t dragon      = model_create(mesh_wavefront_load("bin/models/dragon.obj"));
    model_t triangle    = model_create(mesh_primitive_triangle());
    model_t triangle1    = model_create(mesh_primitive_triangle());

    u_memory_pool_add(&mp, sizeof(model_t), &dragon);
    u_memory_pool_add(&mp, sizeof(model_t), &triangle);
    u_memory_pool_add(&mp, sizeof(model_t), &triangle1);

    printf("%d\n", sizeof(model_t));

    MEMORY_CSTCT(model_t, mp.blocks[0].data).transform.position.z = -25;

    projection = m_projection(45, 4/3, 0.01f, 250.0f);

    camera_t camera = camera_create(
        (vec3_t){ 0.0f, 0.0f, 3.0f },
        (vec3_t){ 0.0f, 0.0f, 0.0f },
        (vec3_t){ 0.0f, 1.0f, 0.0f }
    );

    double lastTime = glfwGetTime();

    while (!glfwWindowShouldClose(pWindow)) {
        window_update(pWindow);

        double currentTime = glfwGetTime();

        if (currentTime >= lastTime + 1.0f / FPS) {
            lastTime = glfwGetTime();

            for (int i = 0; i < mp.length; i++) {
                model_update(&MEMORY_CSTCT(model_t, mp.blocks[i].data));
            }

            camera_drag_look(&camera);

            MEMORY_CSTCT(model_t, mp.blocks[1].data).transform.position = (vec3_t){ 0, 15 * sinf(glfwGetTime()), 15 * cosf(glfwGetTime()) - 25};

            MEMORY_CSTCT(model_t, mp.blocks[2].data).transform.position.z = -20;
            MEMORY_CSTCT(model_t, mp.blocks[2].data).transform.position.y = sinf(glfwGetTime()) * 5;
            MEMORY_CSTCT(model_t, mp.blocks[2].data).transform.position.x = cosf(glfwGetTime()) * 5;
        }

        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);

        for (int i = 0; i < mp.length; i++) {
            GLuint stateShaderID = 0;

            if (i == 1) {
                ogl_shader_use(lightShaderProgramID);
                stateShaderID = lightShaderProgramID;
            } else {
                ogl_shader_use(shaderProgramID);
                stateShaderID = shaderProgramID;
            }

            ogl_shader_uniform_vec3(shaderProgramID, "lightPosition", &MEMORY_CSTCT(model_t, mp.blocks[1].data).transform.position);
            ogl_shader_uniform_mat4(stateShaderID, "projection", &projection);
            ogl_shader_uniform_mat4(stateShaderID, "view", &camera.matrix);
            ogl_shader_uniform_mat4(stateShaderID, "model", &MEMORY_CSTCT(model_t, mp.blocks[i].data).transform.matrix);
            ogl_draw(GL_TRIANGLES, MEMORY_CSTCT(model_t, mp.blocks[i].data).mesh.vaoID, MEMORY_CSTCT(model_t, mp.blocks[i].data).mesh.iCount);
        }
    }

    window_destroy(pWindow);

    u_memory_pool_destroy(&mp);
    
    return 0;
}
