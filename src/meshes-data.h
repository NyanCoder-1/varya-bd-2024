#ifndef _MESHES_DATA_H_
#define _MESHES_DATA_H_

#include "mesh-helper.h"
#include <cglm/types.h>
#include <stdint.h>

// Envelope
extern const struct MeshTextured meshEnvelopeClosedVertices[];
extern const vec3 meshEnvelopeOpenedVerticesPositions[];
extern const vec3 meshEnvelopeControlVerticesPositions[];
extern const uint32_t meshEnvelopeVerticesSize;
extern const uint32_t meshEnvelopeVerticesCount;
extern const uint16_t meshEnvelopeIndices[];
extern const uint32_t meshEnvelopeIndicesSize;
extern const uint32_t meshEnvelopeIndicesCount;

// Pivot
extern const struct MeshColored meshPivotVertices[];
extern const uint32_t meshPivotVerticesSize;
extern const uint32_t meshPivotVerticesCount;
extern const uint16_t meshPivotIndices[];
extern const uint32_t meshPivotIndicesSize;
extern const uint32_t meshPivotIndicesCount;

// Glow
extern const struct MeshTextured meshGlowVertices[];
extern const uint32_t meshGlowVerticesSize;
extern const uint32_t meshGlowVerticesCount;
extern const uint16_t meshGlowIndices[];
extern const uint32_t meshGlowIndicesSize;
extern const uint32_t meshGlowIndicesCount;

// House
extern const struct MeshTextured meshHouseVertices[];
extern const uint32_t meshHouseVerticesSize;
extern const uint32_t meshHouseVerticesCount;
extern const uint16_t meshHouseIndices[];
extern const uint32_t meshHouseIndicesSize;
extern const uint32_t meshHouseIndicesCount;

// Sky
extern const struct MeshTextured meshSkyVertices[];
extern const uint32_t meshSkyVerticesSize;
extern const uint32_t meshSkyVerticesCount;
extern const uint16_t meshSkyIndices[];
extern const uint32_t meshSkyIndicesSize;
extern const uint32_t meshSkyIndicesCount;

#endif // _MESHES_DATA_H_