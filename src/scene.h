#ifndef _SCENE_H_
#define _SCENE_H_

#include <stdint.h>

typedef struct Scene *scene_t;

scene_t sceneCreate();
void sceneDestroy(scene_t *scene);
void sceneUpdate(scene_t scene, const float deltaTime);
void sceneDraw(scene_t scene);
void sceneOnResize(scene_t scene, const uint32_t width, const uint32_t height);
void sceneOnClick(scene_t scene, const uint32_t x, const uint32_t y);

#endif // _SCENE_H_