#include "camera.h"
#include "cglm/types.h"
#include "graphics-types.h"
#include "graphics.h"
#include "mesh-helper.h"
#include "meshes-data.h"
#include "scene.h"
#include <cglm/cglm.h>
#include <GLES3/gl3.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

const vec3 cameraPosition = {0.0f, -5.0f, 0.75f};
const vec3 cameraRotation = {87.0f * GLM_PIf / 180.0f, 0.0f, 0.0f};
const float animationOpeningKeyTime0 = 0.0f;
const float animationOpeningKeyTime1 = 1.0f; // upper fold opening
const float animationOpeningKeyTime2 = 1.25f; // lower fold opening
const float animationOpeningDuration = animationOpeningKeyTime2 - animationOpeningKeyTime0;
const float animationClosingkeyTime0 = 0.0f;
const float animationClosingkeyTime1 = 0.5f; // lower fold closing
const float animationClosingkeyTime2 = 0.75f; // upper fold closing
const float animationClosingDuration = animationClosingkeyTime2 - animationClosingkeyTime0;
const float rotationPeriod = 11.0f;
const float bouncingPeriod = 4.0f;
const vec3 envelopePosition0 = {0.0f, 0.0f, 0.5f};
const vec3 envelopePosition1 = {0.0f, 0.0f, 0.75f};
const vec3 envelopePositionAtCamera = {0.0f, -3.0f, 0.65f};
const vec3 envelopeRotationAtCamera = {0.0f, 0.0f, 0.0f};
const float envelopeStateTransitionDuration = 0.5f;

const vec3 housePosition = {5.0f, 2.5f, 0.0f};
const vec3 treePosition = {-3.65f, -1.0f, 0.5f};

enum eEnvelopeAnimation {
	ENVELOPE_ANIMATION_OPENING,
	ENVELOPE_ANIMATION_CLOSING
};
enum eEnvelopeState {
	ENVELOPE_STATE_DEFAULT,
	ENVELOPE_STATE_FOCUS
};

struct Scene {
	shader_t shader;
	object_t envelope;
	object_t glow;
	object_t glow2;
	object_t house;
	object_t tree;
	object_t sky;
	camera_t camera;
	meshtextured_t meshEnvelopeVertices;
	float animationTime;
	float rotationTime;
	float bouncingTime;
	enum eEnvelopeAnimation envelopeAnimationState;
	double time;
	float envelopeStateTransitionTime;
	enum eEnvelopeState envelopeState;
};

float clamp(float d, float min, float max) {
  const float t = d < min ? min : d;
  return t > max ? max : t;
}
void sceneSetAnimation(scene_t scene, const enum eEnvelopeAnimation animation)
{
	scene->animationTime = 0.0f;
	scene->envelopeAnimationState = animation;
}
void sceneSetEnvelopeState(scene_t scene, const enum eEnvelopeState state)
{
	scene->envelopeStateTransitionTime = 0.0f;
	scene->envelopeState = state;
}
void sceneUpdateEnvelopeAnimation(scene_t scene, const float deltaTime)
{
	scene->animationTime += deltaTime;
	float t0 = 0;
	float t1 = 0;
	if (scene->envelopeAnimationState == ENVELOPE_ANIMATION_OPENING) {
		float t0Duration = animationOpeningKeyTime1 - animationOpeningKeyTime0;
		float t0StartKey = animationOpeningKeyTime0;
		float t1Duration = animationOpeningKeyTime2 - animationOpeningKeyTime1;
		float t1StartKey = animationOpeningKeyTime1;
		t0 = clamp((scene->animationTime - t0StartKey) / t0Duration, 0.0f, 1.0f);
		t1 = clamp((scene->animationTime - t1StartKey) / t1Duration, 0.0f, 1.0f);
		if (scene->animationTime > animationOpeningKeyTime2)
			scene->animationTime = animationOpeningKeyTime2;
	}
	else if (scene->envelopeAnimationState == ENVELOPE_ANIMATION_CLOSING) {
		float t0Duration = animationClosingkeyTime2 - animationClosingkeyTime1;
		float t0EndKey = animationClosingkeyTime2;
		float t1Duration = animationClosingkeyTime1 - animationClosingkeyTime0;
		float t1EndKey = animationClosingkeyTime1;
		t0 = clamp((t0EndKey - scene->animationTime) / t0Duration, 0.0f, 1.0f);
		t1 = clamp((t1EndKey - scene->animationTime) / t1Duration, 0.0f, 1.0f);
		if (scene->animationTime > animationClosingkeyTime2)
			scene->animationTime = animationClosingkeyTime2;
	}
	printf("at: %f, t0: %f, t1: %f\n", scene->animationTime, t0, t1);

	// upper fold
	for (int i = 0; i < 4; ++i) {
#define INTERPOLATE(a, b, c, t) (a*(1.0-t)*(1.0-t) + b*2.0*t*(1.0-t) + c*t*t)
		scene->meshEnvelopeVertices[i].position[0] = INTERPOLATE(meshEnvelopeClosedVertices[i].position[0], meshEnvelopeControlVerticesPositions[i][0], meshEnvelopeOpenedVerticesPositions[i][0], t0);
		scene->meshEnvelopeVertices[i].position[1] = INTERPOLATE(meshEnvelopeClosedVertices[i].position[1], meshEnvelopeControlVerticesPositions[i][1], meshEnvelopeOpenedVerticesPositions[i][1], t0);
		scene->meshEnvelopeVertices[i].position[2] = INTERPOLATE(meshEnvelopeClosedVertices[i].position[2], meshEnvelopeControlVerticesPositions[i][2], meshEnvelopeOpenedVerticesPositions[i][2], t0);
		scene->meshEnvelopeVertices[i + (meshEnvelopeVerticesCount/2)].position[0] = INTERPOLATE(meshEnvelopeClosedVertices[i + (meshEnvelopeVerticesCount/2)].position[0], meshEnvelopeControlVerticesPositions[i + (meshEnvelopeVerticesCount/2)][0], meshEnvelopeOpenedVerticesPositions[i + (meshEnvelopeVerticesCount/2)][0], t0);
		scene->meshEnvelopeVertices[i + (meshEnvelopeVerticesCount/2)].position[1] = INTERPOLATE(meshEnvelopeClosedVertices[i + (meshEnvelopeVerticesCount/2)].position[1], meshEnvelopeControlVerticesPositions[i + (meshEnvelopeVerticesCount/2)][1], meshEnvelopeOpenedVerticesPositions[i + (meshEnvelopeVerticesCount/2)][1], t0);
		scene->meshEnvelopeVertices[i + (meshEnvelopeVerticesCount/2)].position[2] = INTERPOLATE(meshEnvelopeClosedVertices[i + (meshEnvelopeVerticesCount/2)].position[2], meshEnvelopeControlVerticesPositions[i + (meshEnvelopeVerticesCount/2)][2], meshEnvelopeOpenedVerticesPositions[i + (meshEnvelopeVerticesCount/2)][2], t0);
#undef INTERPOLATE
	}
	// lower fold
	for (int i = meshEnvelopeVerticesCount / 2 - 4; i < meshEnvelopeVerticesCount / 2; ++i) {
#define INTERPOLATE(a, b, c, t) (a*(1.0-t)*(1.0-t) + b*2.0*t*(1.0-t) + c*t*t)
		scene->meshEnvelopeVertices[i].position[0] = INTERPOLATE(meshEnvelopeClosedVertices[i].position[0], meshEnvelopeControlVerticesPositions[i][0], meshEnvelopeOpenedVerticesPositions[i][0], t1);
		scene->meshEnvelopeVertices[i].position[1] = INTERPOLATE(meshEnvelopeClosedVertices[i].position[1], meshEnvelopeControlVerticesPositions[i][1], meshEnvelopeOpenedVerticesPositions[i][1], t1);
		scene->meshEnvelopeVertices[i].position[2] = INTERPOLATE(meshEnvelopeClosedVertices[i].position[2], meshEnvelopeControlVerticesPositions[i][2], meshEnvelopeOpenedVerticesPositions[i][2], t1);
		scene->meshEnvelopeVertices[i + (meshEnvelopeVerticesCount/2)].position[0] = INTERPOLATE(meshEnvelopeClosedVertices[i + (meshEnvelopeVerticesCount/2)].position[0], meshEnvelopeControlVerticesPositions[i + (meshEnvelopeVerticesCount/2)][0], meshEnvelopeOpenedVerticesPositions[i + (meshEnvelopeVerticesCount/2)][0], t1);
		scene->meshEnvelopeVertices[i + (meshEnvelopeVerticesCount/2)].position[1] = INTERPOLATE(meshEnvelopeClosedVertices[i + (meshEnvelopeVerticesCount/2)].position[1], meshEnvelopeControlVerticesPositions[i + (meshEnvelopeVerticesCount/2)][1], meshEnvelopeOpenedVerticesPositions[i + (meshEnvelopeVerticesCount/2)][1], t1);
		scene->meshEnvelopeVertices[i + (meshEnvelopeVerticesCount/2)].position[2] = INTERPOLATE(meshEnvelopeClosedVertices[i + (meshEnvelopeVerticesCount/2)].position[2], meshEnvelopeControlVerticesPositions[i + (meshEnvelopeVerticesCount/2)][2], meshEnvelopeOpenedVerticesPositions[i + (meshEnvelopeVerticesCount/2)][2], t1);
#undef INTERPOLATE
	}
	meshUpdateVertices(objectGetMesh(scene->envelope), scene->meshEnvelopeVertices, meshEnvelopeVerticesSize);
	scene->rotationTime += deltaTime;
	scene->rotationTime = fmodf(scene->rotationTime + rotationPeriod / 2.0f, rotationPeriod) - rotationPeriod / 2.0f;
	vec3 rotation = {0.0f, 0.0f, scene->rotationTime / rotationPeriod * GLM_PI * 2.0f};
	vec3 glowRotation = {0.0f, scene->rotationTime / rotationPeriod * GLM_PI * 2.0f, 0.0f};
	vec3 glowRotation2 = {0.0f, -scene->rotationTime / rotationPeriod * GLM_PI * 2.0f, 0.0f};

	scene->bouncingTime += deltaTime;
	scene->bouncingTime = fmodf(scene->bouncingTime, bouncingPeriod);
	float bouncingFactor = sinf(scene->bouncingTime / bouncingPeriod * GLM_PI * 2.0f);
#define INTERPOLATE(a, b, t) (a*(1.0-t) + b*t)
	vec3 position = {
		INTERPOLATE(envelopePosition0[0], envelopePosition1[0], bouncingFactor),
		INTERPOLATE(envelopePosition0[1], envelopePosition1[1], bouncingFactor),
		INTERPOLATE(envelopePosition0[2], envelopePosition1[2], bouncingFactor)
	};
#undef INTERPOLATE

	scene->envelopeStateTransitionTime += deltaTime;
	scene->envelopeStateTransitionTime = clamp(scene->envelopeStateTransitionTime, 0.0f, envelopeStateTransitionDuration);
	float envelopeStateFactor = (scene->envelopeState != ENVELOPE_STATE_DEFAULT) ? scene->envelopeStateTransitionTime / envelopeStateTransitionDuration : 1.0f - scene->envelopeStateTransitionTime / envelopeStateTransitionDuration;

#define INTERPOLATE_VEC3(a, b, t) (vec3){a[0]*(1.0-t) + b[0]*t, a[1]*(1.0-t) + b[1]*t, a[2]*(1.0-t) + b[2]*t}
	vec3 envelopeRotation = INTERPOLATE_VEC3(rotation, envelopeRotationAtCamera, envelopeStateFactor);
	vec3 envelopePosition = INTERPOLATE_VEC3(position, envelopePositionAtCamera, envelopeStateFactor);
#undef INTERPOLATE_VEC3P

	objectSetRotationVec3(scene->envelope, envelopeRotation);
	objectSetPositionVec3(scene->envelope, envelopePosition);

	objectSetRotationVec3(scene->glow, glowRotation);
	objectSetPositionVec3(scene->glow, position);
	objectSetRotationVec3(scene->glow2, glowRotation2);
	objectSetPositionVec3(scene->glow2, position);
}

scene_t sceneCreate()
{
	scene_t scene = (scene_t)malloc(sizeof(struct Scene));
	scene->shader = shaderCreateFromFile("shaders/textured-vs.glsl", "shaders/textured-fs.glsl");

	// Envelope
	texture_t textureEnvelope = textureCreateFromPngFile("images/varya-bd-letter-texture.png");
	scene->meshEnvelopeVertices = (meshtextured_t)malloc(meshEnvelopeVerticesSize);
	memcpy(scene->meshEnvelopeVertices, meshEnvelopeClosedVertices, meshEnvelopeVerticesSize);
	mesh_t meshEnvelope = meshCreate(scene->shader, meshtextured_applyAttributes, (void*)scene->meshEnvelopeVertices, meshEnvelopeVerticesSize, (uint16_t*)meshEnvelopeIndices, meshEnvelopeIndicesSize);
	scene->envelope = objectCreate(meshEnvelope, textureEnvelope, scene->shader, OWN_MESH | OWN_TEXTURE);
	objectSetPositionVec3(scene->envelope, envelopePosition0);

	// Glow
	texture_t textureGlow = textureCreateFromPngFile("images/blue-glow.png");
	mesh_t meshGlow = meshCreate(scene->shader, meshtextured_applyAttributes, (void*)meshGlowVertices, meshGlowVerticesSize, (uint16_t*)meshGlowIndices, meshGlowIndicesSize);
	scene->glow = objectCreate(meshGlow, textureGlow, scene->shader, OWN_MESH | OWN_TEXTURE);
	scene->glow2 = objectCreate(meshGlow, textureGlow, scene->shader, OWN_NONE);
	objectSetPositionVec3(scene->glow, envelopePosition0);
	objectSetPositionVec3(scene->glow2, envelopePosition0);

	// Tree
	texture_t textureTree = textureCreateFromPngFile("images/tree.png");
	scene->tree = objectCreate(meshGlow, textureTree, scene->shader, OWN_TEXTURE);
	objectSetPositionVec3(scene->tree, treePosition);

	// House
	texture_t textureHouse = textureCreateFromPngFile("images/house-atlas.png");
	mesh_t meshHouse = meshCreate(scene->shader, meshtextured_applyAttributes, (void*)meshHouseVertices, meshHouseVerticesSize, (uint16_t*)meshHouseIndices, meshHouseIndicesSize);
	scene->house = objectCreate(meshHouse, textureHouse, scene->shader, OWN_MESH | OWN_TEXTURE);
	objectSetPositionVec3(scene->house, housePosition);

	// Sky
	texture_t textureSky = textureCreateFromPngFile("images/sky.png");
	mesh_t meshSky = meshCreate(scene->shader, meshtextured_applyAttributes, (void*)meshSkyVertices, meshSkyVerticesSize, (uint16_t*)meshSkyIndices, meshSkyIndicesSize);
	scene->sky = objectCreate(meshSky, textureSky, scene->shader, OWN_MESH | OWN_TEXTURE);

	scene->camera = cameraCreate();
	cameraSetPositionVec3(scene->camera, cameraPosition);
	cameraSetRotationVec3(scene->camera, cameraRotation);

	scene->time = 0;
	scene->animationTime = animationClosingDuration;
	scene->envelopeAnimationState = ENVELOPE_ANIMATION_CLOSING;

	scene->envelopeState = ENVELOPE_STATE_DEFAULT;
	scene->envelopeStateTransitionTime = envelopeStateTransitionDuration;

	return scene;
}

void sceneDestroy(scene_t *scene)
{
	if (scene) {
		if ((*scene)->shader) shaderDestroy(&(*scene)->shader);
		if ((*scene)->envelope) objectDestroy(&(*scene)->envelope);
		if ((*scene)->tree) objectDestroy(&(*scene)->tree);
		if ((*scene)->glow2) objectDestroy(&(*scene)->glow2);
		if ((*scene)->glow) objectDestroy(&(*scene)->glow);
		if ((*scene)->house) objectDestroy(&(*scene)->house);
		if ((*scene)->sky) objectDestroy(&(*scene)->sky);
		free(*scene);
		*scene = NULL;
	}
}

const float period = 11.0f;
const float key0 = 0.1f;
const float key1 = 8.0f;

void sceneUpdate(scene_t scene, const float deltaTime)
{
	if (scene) {
		scene->time += deltaTime;
		cameraUpdate(scene->camera);

		sceneUpdateEnvelopeAnimation(scene, deltaTime);
		while (scene->time > period) {
			scene->time -= period;
		}
	}
}

void sceneDraw(scene_t scene)
{
	if (scene) {
		objectDraw(scene->sky, scene->camera);
		objectDraw(scene->house, scene->camera);
		objectDraw(scene->tree, scene->camera);
		glDisable(GL_DEPTH_TEST);
		objectDraw(scene->glow, scene->camera);
		objectDraw(scene->glow2, scene->camera);
		glEnable(GL_DEPTH_TEST);
		objectDraw(scene->envelope, scene->camera);
	}
}

void sceneOnResize(scene_t scene, const uint32_t width, const uint32_t height)
{
	if (scene && width && height) {
		glViewport(0, 0, width, height);
		cameraSetScreenSize(scene->camera, width, height);
		cameraUpdate(scene->camera);
	}
}

void sceneOnClick(scene_t scene, const uint32_t x, const uint32_t y)
{
	if (!scene)
		 return;

	if (scene->envelopeState == ENVELOPE_STATE_DEFAULT) {
		sceneSetAnimation(scene, ENVELOPE_ANIMATION_OPENING);
		sceneSetEnvelopeState(scene, ENVELOPE_STATE_FOCUS);
	} else {
		sceneSetAnimation(scene, ENVELOPE_ANIMATION_CLOSING);
		sceneSetEnvelopeState(scene, ENVELOPE_STATE_DEFAULT);
	}
}
