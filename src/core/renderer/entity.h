#ifndef ENTITY_H
#define ENTITY_H

#include "../../lib/cglm/include/cglm/cglm.h"
#include "ogl.h"

typedef struct entity_t {
    vec3 position;
    vec3 rotation;
    vec3 scale;
    mesh_t mesh;
} entity_t;

entity_t entity_create(vec3 position, vec3 rotation, vec3 scale, mesh_t mesh);
void entity_update(entity_t* entity);

#endif // ENTITY_H
