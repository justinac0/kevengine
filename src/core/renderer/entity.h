#ifndef ENTITY_H
#define ENTITY_H

#include "../util/g_math.h"
#include "ogl.h"

typedef struct entity_t {
    vec3_t position;
    vec3_t rotation;
    vec3_t scale;
    mesh_t mesh;
} entity_t;

entity_t entity_create(vec3_t position, vec3_t rotation, vec3_t scale, mesh_t mesh);
void entity_update(entity_t* entity);

#endif // ENTITY_H
