#define MEM_DEBUG
#include "kevin.h"

#define FPS 120

int main(int argc, char* argv) {
    GLFWwindow* pWindow = window_create(800, 600, "kevin");

    GLuint shaderProgramID, lightShaderProgramID;
    mat4_t projection, view;

    shaderProgramID      = ogl_shader_load("bin/shaders/vertex.glsl",   "bin/shaders/fragment.glsl");
    lightShaderProgramID = ogl_shader_load("bin/shaders/vs_light.glsl", "bin/shaders/fs_light.glsl");

    memory_pool_t mp = memory_pool_create(MEMORY_1MB * 8);

    memory_pool_add(&mp, MEMORY_BLOCK_TAG_RENDER, sizeof(model_t), &(model_t) { m_transform_create(), mesh_primitive_cube() });
    memory_pool_add(&mp, MEMORY_BLOCK_TAG_RENDER, sizeof(model_t), &(model_t) { m_transform_create(), mesh_wavefront_load("bin/models/sphere.obj") });

    projection = m_projection(50, 4/3, 0.01f, 250.0f);

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
                if (mp.blocks[i].tag == MEMORY_BLOCK_TAG_RENDER) {
                    model_update(&MEMORY_BLOCK_CAST_STRUCT(model_t, mp.blocks[i].data));
                }
            }

            camera_drag_look(&camera);

            MEMORY_BLOCK_CAST_STRUCT(model_t, mp.blocks[0].data).transform.rotation.y = 15 * glfwGetTime();
            MEMORY_BLOCK_CAST_STRUCT(model_t, mp.blocks[1].data).transform.position.y = 15 * sinf(glfwGetTime());
            MEMORY_BLOCK_CAST_STRUCT(model_t, mp.blocks[1].data).transform.position.z = 15 * cosf(glfwGetTime());
        }

        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);

        ogl_shader_uniform_vec3(shaderProgramID, "lightPosition", &MEMORY_BLOCK_CAST_STRUCT(model_t, mp.blocks[1].data).transform.position);        
        
        for (int i = 0; i < mp.length; i++) {
            if (mp.blocks[i].tag == MEMORY_BLOCK_TAG_RENDER) {
                GLuint stateShaderID = 0;

                if (i == 1) {
                    ogl_shader_use(lightShaderProgramID);
                    // stateShaderID = lightShaderProgramID;
                } else {
                    ogl_shader_use(shaderProgramID);
                    stateShaderID = shaderProgramID;
                }

                ogl_shader_uniform_mat4(stateShaderID, "projection", &projection);
                ogl_shader_uniform_mat4(stateShaderID, "view", &camera.matrix);
                ogl_shader_uniform_mat4(stateShaderID, "model", &MEMORY_BLOCK_CAST_STRUCT(model_t, mp.blocks[i].data).transform.matrix);
                ogl_draw(GL_TRIANGLES, MEMORY_BLOCK_CAST_STRUCT(model_t, mp.blocks[i].data).mesh.vaoID,
                MEMORY_BLOCK_CAST_STRUCT(model_t, mp.blocks[i].data).mesh.iCount);
            }
        }
    }

    window_destroy(pWindow);

    memory_pool_destroy(&mp);

    return 0;
}
