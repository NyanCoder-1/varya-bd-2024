#include <GLES3/gl3.h>
#include "graphics.h"
#include <emscripten/html5.h>

EM_JS(void, mapCanvas, (void), {
	specialHTMLTargets["!canvas"] = Module.canvas;
})

void initGlContext(void)
{
	mapCanvas();
	EmscriptenWebGLContextAttributes ctxAttrs;
	emscripten_webgl_init_context_attributes(&ctxAttrs);
	ctxAttrs.majorVersion = 2;
	ctxAttrs.minorVersion = 0;
	EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx = emscripten_webgl_create_context("!canvas", &ctxAttrs);
	emscripten_webgl_make_context_current(ctx);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);  
	glDepthMask(GL_TRUE);
}