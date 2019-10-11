#include "model.h"

model_t model_create(mesh_t mesh) {
    model_t model;

    model.position      = m_vec3_zero();
    model.rotation      = m_vec3_zero();
    model.scale         = m_vec3_fill(1.0f);
    model.modelMatrix   = m_mat4_identity();
    model.mesh          = mesh;

    return model;
}

void model_update(model_t* model) {
    // translation
    mat4_t t = m_translate(model->position);
    mat4_t s = m_scale(model->scale);

    model->modelMatrix = t;
}
