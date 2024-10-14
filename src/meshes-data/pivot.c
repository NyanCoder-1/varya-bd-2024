#include "meshes-data.h"

const struct MeshColored meshPivotVertices[] = {
	{ .position = {0.0f, 0.0f, 0.0f }, .color = {1.0f, 0.0f, 0.0f, 1.0f} },
	{ .position = {1.0f, 0.0f, 0.0f }, .color = {1.0f, 0.0f, 0.0f, 1.0f} },
	{ .position = {0.25f, 0.25f, 0.25f }, .color = {1.0f, 0.0f, 0.0f, 1.0f} },

	{ .position = {0.0f, 0.0f, 0.0f }, .color = {0.0f, 1.0f, 0.0f, 1.0f} },
	{ .position = {0.0f, 1.0f, 0.0f }, .color = {0.0f, 1.0f, 0.0f, 1.0f} },
	{ .position = {0.25f, 0.25f, 0.25f }, .color = {0.0f, 1.0f, 0.0f, 1.0f} },

	{ .position = {0.0f, 0.0f, 0.0f }, .color = {0.0f, 0.0f, 1.0f, 1.0f} },
	{ .position = {0.0f, 0.0f, 1.0f }, .color = {0.0f, 0.0f, 1.0f, 1.0f} },
	{ .position = {0.25f, 0.25f, 0.25f }, .color = {0.0f, 0.0f, 1.0f, 1.0f} },
};
const uint32_t meshPivotVerticesSize = sizeof(meshPivotVertices);
const uint32_t meshPivotVerticesCount = sizeof(meshPivotVertices) / sizeof(struct MeshColored);

const uint16_t meshPivotIndices[] = {
	0, 1, 2,
	0, 2, 1,

	3, 4, 5,
	3, 5, 4,

	6, 7, 8,
	6, 8, 7,
};
const uint32_t meshPivotIndicesSize = sizeof(meshPivotIndices);
const uint32_t meshPivotIndicesCount = sizeof(meshPivotIndices) / sizeof(uint16_t);
