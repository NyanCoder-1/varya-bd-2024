#include "meshes-data.h"

const struct MeshTextured meshEnvelopeClosedVertices[] = {
	// back page
	{ .position = {-1.0f, -0.01f, -0.5f }, .texcoord = {0.5f, 0.0f} },
	{ .position = {1.0f, -0.01f, -0.5f }, .texcoord = {1.0f, 0.0f} },
	{ .position = {-1.0f, -0.01f, 0.5f }, .texcoord = {0.5f, 0.316406f} },
	{ .position = {1.0f, -0.01f, 0.5f }, .texcoord = {1.0f, 0.316406f} },
	{ .position = {-1.0f, 0.01f, 0.5f }, .texcoord = {0.5f, 0.324219f} },
	{ .position = {1.0f, 0.01f, 0.5f }, .texcoord = {1.0f, 0.324219f} },
	{ .position = {-1.0f, 0.01f, -0.5f }, .texcoord = {0.5f, 0.660156f} },
	{ .position = {1.0f, 0.01f, -0.5f }, .texcoord = {1.0f, 0.660156f} },
	{ .position = {-1.0f, -0.01f, -0.5f }, .texcoord = {0.5f, 0.667969f} },
	{ .position = {1.0f, -0.01f, -0.5f }, .texcoord = {1.0f, 0.667969f} },
	{ .position = {-1.0f, 0.0f, 0.49f }, .texcoord = {0.5f, 1.0f} },
	{ .position = {1.0f, 0.0f, 0.49f }, .texcoord = {1.0f, 1.0f} },

	// inside
	{ .position = {-1.0f, -0.01f, -0.5f }, .texcoord = {0.0f, 0.0f} },
	{ .position = {1.0f, -0.01f, -0.5f }, .texcoord = {0.5f, 0.0f} },
	{ .position = {-1.0f, -0.01f, 0.5f }, .texcoord = {0.0f, 0.316406f} },
	{ .position = {1.0f, -0.01f, 0.5f }, .texcoord = {0.5f, 0.316406f} },
	{ .position = {-1.0f, 0.01f, 0.5f }, .texcoord = {0.0f, 0.324219f} },
	{ .position = {1.0f, 0.01f, 0.5f }, .texcoord = {0.5f, 0.324219f} },
	{ .position = {-1.0f, 0.01f, -0.5f }, .texcoord = {0.0f, 0.660156f} },
	{ .position = {1.0f, 0.01f, -0.5f }, .texcoord = {0.5f, 0.660156f} },
	{ .position = {-1.0f, -0.01f, -0.5f }, .texcoord = {0.0f, 0.667969f} },
	{ .position = {1.0f, -0.01f, -0.5f }, .texcoord = {0.5f, 0.667969f} },
	{ .position = {-1.0f, 0.0f, 0.49f }, .texcoord = {0.0f, 1.0f} },
	{ .position = {1.0f, 0.0f, 0.49f }, .texcoord = {0.5f, 1.0f} },
};
const uint32_t meshEnvelopeVerticesSize = sizeof(meshEnvelopeClosedVertices);
const uint32_t meshEnvelopeVerticesCount = meshEnvelopeVerticesSize / sizeof(struct MeshTextured);

const vec3 meshEnvelopeOpenedVerticesPositions[] = {
	// back page
	{ -1.0f, -0.27f, 1.4f },
	{ 1.0f, -0.27f, 1.4f },
	{ -1.0f, 0.005f, 0.505f },
	{ 1.0f, 0.005f, 0.505f },
	{ -1.0f, 0.01f, 0.5f },
	{ 1.0f, 0.01f, 0.5f },
	{ -1.0f, 0.01f, -0.5f },
	{ 1.0f, 0.01f, -0.5f },
	{ -1.0f, 0.005f, -0.505f },
	{ 1.0f, 0.005f, -0.505f },
	{ -1.0f, -0.46f, -1.44f },
	{ 1.0f, -0.46f, -1.44f },

	// inside
	{ -1.0f, -0.27f, 1.4f },
	{ 1.0f, -0.27f, 1.4f },
	{ -1.0f, 0.005f, 0.505f },
	{ 1.0f, 0.005f, 0.505f },
	{ -1.0f, 0.01f, 0.5f },
	{ 1.0f, 0.01f, 0.5f },
	{ -1.0f, 0.01f, -0.5f },
	{ 1.0f, 0.01f, -0.5f },
	{ -1.0f, 0.005f, -0.505f },
	{ 1.0f, 0.005f, -0.505f },
	{ -1.0f, -0.46f, -1.44f },
	{ 1.0f, -0.46f, -1.44f },
};
const vec3 meshEnvelopeControlVerticesPositions[] = {
	// back page
	{-1.0f, -2.23f, 0.24f },
	{1.0f, -2.23f, 0.24f },
	{-1.0f, 0.005f, 0.505f },
	{1.0f, 0.005f, 0.505f },
	{-1.0f, 0.01f, 0.5f },
	{1.0f, 0.01f, 0.5f },
	{-1.0f, 0.01f, -0.5f },
	{1.0f, 0.01f, -0.5f },
	{-1.0f, 0.005f, -0.505f },
	{1.0f, 0.005f, -0.505f },
	{-1.0f, -2.23f, 0.0f },
	{1.0f, -2.23f, 0.0f },
	// inside
	{-1.0f, -2.23f, 0.24f },
	{1.0f, -2.23f, 0.24f },
	{-1.0f, 0.005f, 0.505f },
	{1.0f, 0.005f, 0.505f },
	{-1.0f, 0.01f, 0.5f },
	{1.0f, 0.01f, 0.5f },
	{-1.0f, 0.01f, -0.5f },
	{1.0f, 0.01f, -0.5f },
	{-1.0f, 0.005f, -0.505f },
	{1.0f, 0.005f, -0.505f },
	{-1.0f, -2.23f, 0.0f },
	{1.0f, -2.23f, 0.0f },
};

const uint16_t meshEnvelopeIndices[] = {
	// back page
	2, 0, 1,
	3, 2, 1,

	4, 2, 3,
	5, 4, 3,

	6, 4, 5,
	7, 6, 5,

	8, 6, 7,
	9, 8, 7,

	10,8,  9,
	11,10,  9,

	// contents
	13,12,  14,
	13,14,  15,

	15,14,  16,
	15,16,  17,

	17,16,  18,
	17,18,  19,

	19,18,  20,
	19,20,  21,

	21,20,  22,
	21,22,  23
};
const uint32_t meshEnvelopeIndicesSize = sizeof(meshEnvelopeIndices);
const uint32_t meshEnvelopeIndicesCount = sizeof(meshEnvelopeIndices) / sizeof(uint16_t);
