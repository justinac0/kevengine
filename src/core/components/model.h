#ifndef MODEL_H
#define MODEL_H

#include "../utility/math.h"
#include "../renderer/mesh.h"

typedef struct {
    transform_t transform;
    mesh_t      mesh;
} model_t;

model_t model_create(mesh_t mesh);
void model_update(model_t* model);

#endif // MODEL_H
