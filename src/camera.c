#include "camera.h"
#include "cglm/affine-mat.h"
#include "cglm/mat4.h"
#include "cglm/util.h"
#include <GLES3/gl3.h>
#include <cglm/cglm.h>

struct Camera {
	vec3 position;
	vec3 rotation;

	uint32_t screenWidth;
	uint32_t screenHeight;

	mat4 matrixViewProjection;
};

camera_t cameraCreate()
{
	camera_t camera = (camera_t)malloc(sizeof(struct Camera));
	glm_vec3_zero(camera->position);
	glm_vec3_zero(camera->rotation);
	return camera;
}

void cameraDestroy(camera_t *camera)
{
	if (camera) {
		free(*camera);
		*camera = NULL;
	}
}

void cameraSetScreenSize(camera_t camera, const uint32_t width, const uint32_t height)
{
	if (!camera)
		return;

	camera->screenWidth = width;
	camera->screenHeight = height;
}

void cameraSetPosition(camera_t camera, const float x, const float y, const float z)
{
	if (!camera)
		return;
	camera->position[0] = x;
	camera->position[1] = y;
	camera->position[2] = z;
}
void cameraGetPosition(camera_t camera, /* out */ float *x, /* out */ float *y, /* out */ float *z)
{
	if (!camera)
		return;
	if (x) *x = camera->position[0];
	if (y) *y = camera->position[1];
	if (z) *z = camera->position[2];
}
void cameraSetPositionVec3(camera_t camera, const vec3 position)
{
	if (!camera || !position)
		return;
	camera->position[0] = position[0];
	camera->position[1] = position[1];
	camera->position[2] = position[2];
}
void cameraGetPositionVec3(camera_t camera, /* out */ vec3 position)
{
	if (!camera || !position)
		return;
	position[0] = camera->position[0];
	position[1] = camera->position[1];
	position[2] = camera->position[2];
}
void cameraSetRotation(camera_t camera, const float x, const float y, const float z)
{
	if (!camera)
		return;
	camera->rotation[0] = x;
	camera->rotation[1] = y;
	camera->rotation[2] = z;
}
void cameraGetRotation(camera_t camera, /* out */ float *x, /* out */ float *y, /* out */ float *z)
{
	if (!camera)
		return;
	if (x) *x = camera->rotation[0];
	if (y) *y = camera->rotation[1];
	if (z) *z = camera->rotation[2];
}
void cameraSetRotationVec3(camera_t camera, const vec3 rotation)
{
	if (!camera || !rotation)
		return;
	camera->rotation[0] = rotation[0];
	camera->rotation[1] = rotation[1];
	camera->rotation[2] = rotation[2];
}
void cameraGetRotationVec3(camera_t camera, /* out */ vec3 rotation)
{
	if (!camera || !rotation)
		return;
	rotation[0] = camera->rotation[0];
	rotation[1] = camera->rotation[1];
	rotation[2] = camera->rotation[2];
}

void cameraUpdate(camera_t camera)
{
	if (!camera)
		return;

	mat4 view = GLM_MAT4_IDENTITY;
	mat4 viewRotation = GLM_MAT4_IDENTITY;
	glm_euler((vec3){-camera->rotation[0], -camera->rotation[1], -camera->rotation[2]}, viewRotation);
	glm_translate(view, (vec3){-camera->position[0], -camera->position[1], -camera->position[2]});
	glm_mul(viewRotation, view, view);

	mat4 projection = GLM_MAT4_IDENTITY;
	glm_perspective(glm_rad(90.0f), (float)camera->screenWidth / (float)camera->screenHeight, 0.1f, 100.0f, projection);

	glm_mat4_mul(projection, view, camera->matrixViewProjection);
}

void cameraGetMatrix(camera_t camera, /* out */ mat4 matrix)
{
	if (!camera || !matrix)
		return;

	glm_mat4_copy(camera->matrixViewProjection, matrix);
}
