#include "meshes-data.h"

const struct MeshTextured meshSkyVertices[] = {
	// cloud1
	{ .position = {-8.5f, 2.0f, 5.0f }, .texcoord = {0.0f, 0.0f} },
	{ .position = {-6.5f, 2.0f, 5.0f }, .texcoord = {0.5f, 0.0f} },
	{ .position = {-8.5f, 2.0f, 3.0f }, .texcoord = {0.0f, 0.5f} },
	{ .position = {-6.5f, 2.0f, 3.0f }, .texcoord = {0.5f, 0.5f} },

	// cloud2
	{ .position = {-2.9f, 2.0f, 6.2f }, .texcoord = {0.5f, 0.0f} },
	{ .position = {-0.9f, 2.0f, 6.2f }, .texcoord = {1.0f, 0.0f} },
	{ .position = {-2.9f, 2.0f, 4.2f }, .texcoord = {0.5f, 0.5f} },
	{ .position = {-0.9f, 2.0f, 4.2f }, .texcoord = {1.0f, 0.5f} },

	// cloud3
	{ .position = {2.5f, 2.0f, 5.0f }, .texcoord = {0.0f, 0.5f} },
	{ .position = {4.5f, 2.0f, 5.0f }, .texcoord = {0.5f, 0.5f} },
	{ .position = {2.5f, 2.0f, 3.0f }, .texcoord = {0.0f, 1.0f} },
	{ .position = {4.5f, 2.0f, 3.0f }, .texcoord = {0.5f, 1.0f} },

	// sun
	{ .position = {6.85f, 2.0f, 6.3f }, .texcoord = {0.5f, 0.5f} },
	{ .position = {8.85f, 2.0f, 6.3f }, .texcoord = {1.0f, 0.5f} },
	{ .position = {6.85f, 2.0f, 4.3f }, .texcoord = {0.5f, 1.0f} },
	{ .position = {8.85f, 2.0f, 4.3f }, .texcoord = {1.0f, 1.0f} },
};
const uint32_t meshSkyVerticesSize = sizeof(meshSkyVertices);
const uint32_t meshSkyVerticesCount = sizeof(meshSkyVertices) / sizeof(struct MeshTextured);

const uint16_t meshSkyIndices[] = {
	0, 1, 2,
	2, 1, 3,
	0, 2, 1,
	2, 3, 1,

	4, 5, 6,
	6, 5, 7,
	4, 6, 5,
	6, 7, 5,

	8, 9, 10,
	10, 9, 11,
	8, 10, 9,
	10, 11, 9,

	12, 13, 14,
	14, 13, 15,
	12, 14, 13,
	14, 15, 13,
};
const uint32_t meshSkyIndicesSize = sizeof(meshSkyIndices);
const uint32_t meshSkyIndicesCount = sizeof(meshSkyIndices) / sizeof(uint16_t);
