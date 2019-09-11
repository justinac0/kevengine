#include "entity.h"

entity_t entity_create(vec3_t position, vec3_t rotation, vec3_t scale, mesh_t mesh) {
    entity_t entity;
    entity.position = position;
    entity.rotation = rotation;
    entity.scale    = scale;
    entity.mesh     = mesh;

    return entity;
}

void entity_update(entity_t* entity) {
    mat4_t translation ,rotation, scale;
}
