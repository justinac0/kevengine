#ifndef GAME_H
#define GAME_H

#define U_MEM_DEBUG
#include "util.h"
#include "renderer.h"

void g_create(void);
void g_destroy(void);
void g_update(void);
void g_render(void);

#endif // GAME_H