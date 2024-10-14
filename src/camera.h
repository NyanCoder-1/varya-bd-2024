#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "camera-types.h"
#include <cglm/cglm.h>
#include <stdint.h>

camera_t cameraCreate();
void cameraDestroy(camera_t *camera);
void cameraSetScreenSize(camera_t camera, const uint32_t width, const uint32_t height);
void cameraSetPosition(camera_t camera, const float x, const float y, const float z);
void cameraGetPosition(camera_t camera, /* out */ float *x, /* out */ float *y, /* out */ float *z);
void cameraSetPositionVec3(camera_t camera, const vec3 position);
void cameraGetPositionVec3(camera_t camera, /* out */ vec3 position);
void cameraSetRotation(camera_t camera, const float x, const float y, const float z);
void cameraGetRotation(camera_t camera, /* out */ float *x, /* out */ float *y, /* out */ float *z);
void cameraSetRotationVec3(camera_t camera, const vec3 rotation);
void cameraGetRotationVec3(camera_t camera, /* out */ vec3 rotation);
void cameraUpdate(camera_t camera);
void cameraGetMatrix(camera_t camera, /* out */ mat4 matrix);

#endif // _CAMERA_H_