#include "entity.h"

entity_t entity_create(vec3 position, vec3 rotation, vec3 scale, mesh_t mesh) {
    entity_t entity;
    
    glm_vec3_copy(position, entity.position);
    glm_vec3_copy(rotation, entity.rotation);
    glm_vec3_copy(scale, entity.scale);

    entity.mesh     = mesh;

    return entity;
}

void entity_update(entity_t* entity) {
    mat4 t, r, s;

    glm_translate(t, entity->position);
    glm_rotate(r, 1.0f, entity->rotation);
    glm_scale(s, entity->scale);

    glm_mat4_mul(entity->mesh.modelMatrix, r, t);
    glm_mat4_mul(entity->mesh.modelMatrix, s, entity->mesh.modelMatrix);
}
