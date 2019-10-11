#ifndef MODEL_H
#define MODEL_H

#include "../utility/math.h"
#include "../renderer/mesh.h"

typedef struct {
    vec3_t position;
    vec3_t rotation;
    vec3_t scale;
    mat4_t modelMatrix;
    mesh_t mesh;
} model_t;

model_t model_create(mesh_t mesh);
void model_update(model_t* model);

#endif // MODEL_H