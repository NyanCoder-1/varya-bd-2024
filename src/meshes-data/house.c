#include "meshes-data.h"

const struct MeshTextured meshHouseVertices[] = {
	// Front
	{ .position = {-1.03f, -1.0f, -1.0f }, .texcoord = {0.5f, 1.0f} },
	{ .position = {-1.03f, -1.0f, 1.0f }, .texcoord = {0.5f, 0.5f} },
	{ .position = {1.03f, -1.0f, 1.0f }, .texcoord = {1.0f, 0.5f} },
	{ .position = {1.03f, -1.0f, -1.0f }, .texcoord = {1.0f, 1.0f} },

	// Side
	{ .position = {-1.0f, 1.03f, -1.0f }, .texcoord = {0.0f, 1.0f} },
	{ .position = {-1.0f, 1.03f, 1.0f }, .texcoord = {0.0f, 0.5f} },
	{ .position = {-1.0f, -1.03f, 1.0f }, .texcoord = {0.5f, 0.5f} },
	{ .position = {-1.0f, -1.03f, -1.0f }, .texcoord = {0.5f, 1.0f} },

	// Roof-side
	{ .position = {-1.03f, 1.03f, 0.95f }, .texcoord = {0.0f, 0.5f} },
	{ .position = {0.0f, 1.03f, 2.0f }, .texcoord = {0.0f, 0.25f} },
	{ .position = {0.0f, -1.03f, 2.0f }, .texcoord = {0.5f, 0.25f} },
	{ .position = {-1.03f, -1.03f, 0.95f }, .texcoord = {0.5f, 0.5f} },

	// Roof-front
	{ .position = {-1.03f, -1.03f, 0.95f }, .texcoord = {0.5f, 0.5f} },
	{ .position = {0.0f, -1.03f, 2.0f }, .texcoord = {0.74f, 0.25f} },
	{ .position = {1.03f, -1.03f, 0.95f }, .texcoord = {1.0f, 0.495f} },

	// Chimney
	{ .position = {0.60f, -0.8f, 1.35f }, .texcoord = {0.85f, 0.25f} },
	{ .position = {0.60f, -0.8f, 1.75f }, .texcoord = {0.85f, 0.02f} },
	{ .position = {0.85f, -0.8f, 1.75f }, .texcoord = {1.0f, 0.02f} },
	{ .position = {0.85f, -0.8f, 1.35f }, .texcoord = {1.0f, 0.25f} },

	// Smoke
	{ .position = {0.56f, -0.79f, 1.5f }, .texcoord = {0.0f, 0.23f} },
	{ .position = {0.155f, -0.79f, 2.13f }, .texcoord = {0.0f, 0.0f} },
	{ .position = {2.26, -0.79f, 3.575f }, .texcoord = {0.75f, 0.0f} },
	{ .position = {3.06f, -0.79f, 2.38f }, .texcoord = {0.75f, 0.23f} },
};
const uint32_t meshHouseVerticesSize = sizeof(meshHouseVertices);
const uint32_t meshHouseVerticesCount = sizeof(meshHouseVertices) / sizeof(struct MeshTextured);

const uint16_t meshHouseIndices[] = {
	// Smoke
	20, 19, 21,
	21, 19, 22,
	// Chimney
	16, 15, 17,
	17, 15, 18,
	// Roof-side
	9, 8, 10,
	10, 8, 11,
	// Roof-front
	13, 12, 14,
	// Side
	5, 4, 6,
	6, 4, 7,
	// Front
	1, 0, 2,
	2, 0, 3,
};
const uint32_t meshHouseIndicesSize = sizeof(meshHouseIndices);
const uint32_t meshHouseIndicesCount = sizeof(meshHouseIndices) / sizeof(uint16_t);
