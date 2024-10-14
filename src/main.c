#include "graphics.h"
#include "scene.h"
#include <emscripten.h>
#include <GLES3/gl3.h>
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#include <sys/time.h>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include <stb_image.h>

typedef struct UserData {
	scene_t scene;
	struct timeval prevTime;
} *userdata_t;

void mainLoop(void *arg)
{
	if (arg) {
		userdata_t userData = (userdata_t)arg;
		struct timeval curTime;
		gettimeofday(&curTime, NULL);

		float deltaTime = (curTime.tv_sec - userData->prevTime.tv_sec) + (curTime.tv_usec - userData->prevTime.tv_usec) / 1000000.0f;
		userData->prevTime = curTime;
		sceneUpdate(userData->scene, deltaTime);

		// glClearColor(0.5f, 0.5f, 0.2f, 1.0f);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		sceneDraw(userData->scene);
	}
}

bool clickCallback(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData)
{
	if (!userData)
		return false;
	if (eventType == EMSCRIPTEN_EVENT_CLICK) {
		userdata_t myUserData = (userdata_t)userData;
		sceneOnClick(myUserData->scene, mouseEvent->clientX, mouseEvent->clientY);
	}
	return true;
}

bool resizeCallback(int eventType, const EmscriptenUiEvent *uiEvent, void *userData)
{
	if (!userData)
		return false;
	if (eventType == EMSCRIPTEN_EVENT_RESIZE) {
		userdata_t myUserData = (userdata_t)userData;
		int width = uiEvent->documentBodyClientWidth;
		int height = uiEvent->documentBodyClientHeight;
		emscripten_get_canvas_element_size("!canvas", &width, &height);
		if ((width > 0) && (height > 0)) {
			sceneOnResize(myUserData->scene, width, height);
		}
	}
	return true;
}

int main(int argc, char *argv[])
{
	initGlContext();

	struct UserData userData;
	userData.scene = sceneCreate();

	emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, &userData, EM_FALSE, resizeCallback);
	int width = 1920, height = 1080;
	emscripten_get_canvas_element_size("!canvas", &width, &height);
	sceneOnResize(userData.scene, (width > 0) ? width : 1920, (height > 0) ? height : 1080);
	emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, &userData, EM_FALSE, clickCallback);

	gettimeofday(&userData.prevTime, NULL);
	emscripten_set_main_loop_arg(mainLoop, &userData, 0, EM_TRUE);

	sceneDestroy(&userData.scene);

	return 0;
}