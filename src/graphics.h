#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "camera-types.h"
#include "graphics-types.h"
#include <cglm/cglm.h>
#include <emscripten/html5.h>
#include <GLES3/gl3.h>
#include <stdbool.h>
#include <stdint.h>

void initGlContext();

// Game Object
object_t objectCreate(mesh_t mesh, texture_t texture, shader_t shader, const ownflags_t ownFlags);
void objectDestroy(object_t *object);
void objectDraw(object_t object, camera_t camera);
void objectSetPosition(object_t object, const float x, const float y, const float z);
void objectGetPosition(object_t object, /* out */ float *x, /* out */ float *y, /* out */ float *z);
void objectSetPositionVec3(object_t object, const vec3 position);
void objectGetPositionVec3(object_t object, /* out */ vec3 position);
void objectSetRotation(object_t object, const float x, const float y, const float z);
void objectGetRotation(object_t object, /* out */ float *x, /* out */ float *y, /* out */ float *z);
void objectSetRotationVec3(object_t object, const vec3 rotation);
void objectGetRotationVec3(object_t object, /* out */ vec3 rotation);
mesh_t objectGetMesh(object_t object);

// Shader
shader_t shaderCreateFromFile(const char *vertexShaderPath, const char *fragmentShaderPath);
shader_t shaderCreateFromMemory(const char *vertexShaderSource, const uint32_t vertexShaderSourceSize, const char *fragmentShaderSource, const uint32_t fragmentShaderSourceSize);
void shaderDestroy(shader_t *shader);
GLuint shaderGetProgram(shader_t shader);
void shaderUse(shader_t shader);

// Texture
texture_t textureCreateFromPngFile(const char *pngPath);
texture_t textureCreateFromPngInMemory(const char *pngData, const uint32_t pngDataSize);
void textureDestroy(texture_t *texture);
void textureUse(texture_t texture);

// Mesh (static)
mesh_t meshCreate(shader_t shader, void (*applyAttributesFn)(shader_t), const void *vertexData, const uint32_t vertexDataSize, const uint16_t *indicesData, const uint32_t indicesDataSize);
void meshDestroy(mesh_t *mesh);
void meshUpdateVertices(mesh_t mesh, const void *vertexData, const uint32_t vertexDataSize);
void meshDraw(mesh_t mesh);

#endif // _GRAPHICS_H_