#include "meshes-data.h"

const struct MeshTextured meshGlowVertices[] = {
	{ .position = {-1.0f, 0.0f, 1.0f }, .texcoord = {0.0f, 0.0f} },
	{ .position = {1.0f, 0.0f, 1.0f }, .texcoord = {1.0f, 0.0f} },
	{ .position = {-1.0f, 0.0f, -1.0f }, .texcoord = {0.0f, 1.0f} },
	{ .position = {1.0f, 0.0f, -1.0f }, .texcoord = {1.0f, 1.0f} },
};
const uint32_t meshGlowVerticesSize = sizeof(meshGlowVertices);
const uint32_t meshGlowVerticesCount = sizeof(meshGlowVertices) / sizeof(struct MeshTextured);

const uint16_t meshGlowIndices[] = {
	0, 1, 2,
	2, 1, 3,
	0, 2, 1,
	2, 3, 1,
};
const uint32_t meshGlowIndicesSize = sizeof(meshGlowIndices);
const uint32_t meshGlowIndicesCount = sizeof(meshGlowIndices) / sizeof(uint16_t);
