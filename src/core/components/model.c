#include "model.h"

model_t model_create(mesh_t mesh) {
    model_t model;

    model.transform.position    = m_vec3_zero();
    model.transform.rotation    = m_vec3_zero();
    model.transform.scale       = m_vec3_fill(1.f);
    model.mesh                  = mesh;

    return model;
}

void model_update(model_t* model) {
    m_transform_update(&model->transform);
}
