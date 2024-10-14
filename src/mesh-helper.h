#ifndef _MESH_HELPER_H_
#define _MESH_HELPER_H_

#include "graphics.h"

typedef struct MeshColored {
	float position[3];
	float color[4];
} *meshcolored_t;
typedef struct MeshTextured {
	float position[3];
	float texcoord[2];
} *meshtextured_t;

void meshcolored_applyAttributes(shader_t program);
void meshtextured_applyAttributes(shader_t program);

#endif // _MESH_HELPER_H_