#include "camera.h"
#include "cglm/affine-mat.h"
#include "cglm/mat4.h"
#include "graphics.h"
#include <GLES3/gl3.h>
#include <cglm/cglm.h>

struct Object {
	mesh_t mesh;
	texture_t texture;
	shader_t shader;
	GLint locationMatModel;
	GLint locationMatViewProjection;
	ownflags_t ownFlags;
	vec3 position;
	vec3 rotation;
};

object_t objectCreate(mesh_t mesh, texture_t texture, shader_t shader, const ownflags_t ownFlags) {
	object_t object = (object_t)malloc(sizeof(struct Object));
	object->mesh = mesh;
	object->texture = texture;
	object->shader = shader;
	object->ownFlags = ownFlags;
	if (object->shader) {
		const GLuint program = shaderGetProgram(object->shader);
		object->locationMatModel = glGetUniformLocation(program, "matModel");
		object->locationMatViewProjection = glGetUniformLocation(program, "matViewProjection");
	}
	glm_vec3_zero(object->position);
	glm_vec3_zero(object->rotation);
	return object;
}

void objectDestroy(object_t *object) {
	if (object) {
		if ((*object)->ownFlags & OWN_MESH)
			meshDestroy(&(*object)->mesh);
		if ((*object)->ownFlags & OWN_TEXTURE)
			textureDestroy(&(*object)->texture);
		if ((*object)->ownFlags & OWN_SHADER)
			shaderDestroy(&(*object)->shader);
		(*object)->ownFlags = OWN_NONE;
		free(*object);
		*object = NULL;
	}
}

void objectDraw(object_t object, camera_t camera) {
	shaderUse(object->shader);
	textureUse(object->texture);

	// Transform Model
	mat4 objectMatrixRotation;
	glm_euler(object->rotation, objectMatrixRotation);
	mat4 objectMatrixTranslation = GLM_MAT4_IDENTITY;
	glm_translate(objectMatrixTranslation, object->position);
	mat4 objectMatrix = GLM_MAT4_IDENTITY;
	glm_mul(objectMatrixTranslation, objectMatrixRotation, objectMatrix);
	glUniformMatrix4fv(object->locationMatModel, 1, GL_TRUE, (GLfloat*)objectMatrix);

	// Set Camera
	mat4 viewProjectionMatrix;
	cameraGetMatrix(camera, viewProjectionMatrix);
	glUniformMatrix4fv(object->locationMatViewProjection, 1, GL_TRUE, (GLfloat*)viewProjectionMatrix);

	meshDraw(object->mesh);
}

void objectSetPosition(object_t object, const float x, const float y, const float z)
{
	if (!object)
		return;
	object->position[0] = x;
	object->position[1] = y;
	object->position[2] = z;
}
void objectGetPosition(object_t object, /* out */ float *x, /* out */ float *y, /* out */ float *z)
{
	if (!object)
		return;
	if (x) *x = object->position[0];
	if (y) *y = object->position[1];
	if (z) *z = object->position[2];
}
void objectSetPositionVec3(object_t object, const vec3 position)
{
	if (!object || !position)
		return;
	object->position[0] = position[0];
	object->position[1] = position[1];
	object->position[2] = position[2];
}
void objectGetPositionVec3(object_t object, /* out */ vec3 position)
{
	if (!object || !position)
		return;
	position[0] = object->position[0];
	position[1] = object->position[1];
	position[2] = object->position[2];
}
void objectSetRotation(object_t object, const float x, const float y, const float z)
{
	if (!object)
		return;
	object->rotation[0] = x;
	object->rotation[1] = y;
	object->rotation[2] = z;
}
void objectGetRotation(object_t object, /* out */ float *x, /* out */ float *y, /* out */ float *z)
{
	if (!object)
		return;
	if (x) *x = object->rotation[0];
	if (y) *y = object->rotation[1];
	if (z) *z = object->rotation[2];
}
void objectSetRotationVec3(object_t object, const vec3 rotation)
{
	if (!object || !rotation)
		return;
	object->rotation[0] = rotation[0];
	object->rotation[1] = rotation[1];
	object->rotation[2] = rotation[2];
}
void objectGetRotationVec3(object_t object, /* out */ vec3 rotation)
{
	if (!object || !rotation)
		return;
	rotation[0] = object->rotation[0];
	rotation[1] = object->rotation[1];
	rotation[2] = object->rotation[2];
}

mesh_t objectGetMesh(object_t object)
{
	if (!object)
		return NULL;
	return object->mesh;
}
