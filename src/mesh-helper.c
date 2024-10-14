#include "mesh-helper.h"
#include <time.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
const GLint MESHCOLORED_POSITION_ARRAY_SIZE = (GLint)ARRAY_SIZE(((meshcolored_t)NULL)->position);
const void* MESHCOLORED_POSITION_OFFSET = (void*)offsetof(struct MeshColored, position);
const GLint MESHCOLORED_COLOR_ARRAY_SIZE = (GLint)ARRAY_SIZE(((meshcolored_t)NULL)->color);
const void* MESHCOLORED_COLOR_OFFSET = (void*)offsetof(struct MeshColored, color);
const GLint MESHTEXTURED_POSITION_ARRAY_SIZE = (GLint)ARRAY_SIZE(((meshtextured_t)NULL)->position);
const void* MESHTEXTURED_POSITION_OFFSET = (void*)offsetof(struct MeshTextured, position);
const GLint MESHTEXTURED_TEXCOORD_ARRAY_SIZE = (GLint)ARRAY_SIZE(((meshtextured_t)NULL)->texcoord);
const void* MESHTEXTURED_TEXCOORD_OFFSET = (void*)offsetof(struct MeshTextured, texcoord);

void meshcolored_applyAttributes(shader_t shader)
{
	GLint positionAttrib = glGetAttribLocation(shaderGetProgram(shader), "inPos");
	GLint colorAttrib = glGetAttribLocation(shaderGetProgram(shader), "inColor");
	glEnableVertexAttribArray(positionAttrib);
	glVertexAttribPointer(positionAttrib, MESHCOLORED_POSITION_ARRAY_SIZE, GL_FLOAT, GL_FALSE, sizeof(struct MeshColored), MESHCOLORED_POSITION_OFFSET);
	glEnableVertexAttribArray(colorAttrib);
	glVertexAttribPointer(colorAttrib, MESHCOLORED_COLOR_ARRAY_SIZE, GL_FLOAT, GL_FALSE, sizeof(struct MeshColored), MESHCOLORED_COLOR_OFFSET);
}

void meshtextured_applyAttributes(shader_t shader)
{
	GLint positionAttrib = glGetAttribLocation(shaderGetProgram(shader), "inPos");
	GLint texcoordAttrib = glGetAttribLocation(shaderGetProgram(shader), "inUv");
	glEnableVertexAttribArray(positionAttrib);
	glVertexAttribPointer(positionAttrib, MESHTEXTURED_POSITION_ARRAY_SIZE, GL_FLOAT, GL_FALSE, sizeof(struct MeshTextured), MESHTEXTURED_POSITION_OFFSET);
	glEnableVertexAttribArray(texcoordAttrib);
	glVertexAttribPointer(texcoordAttrib, MESHTEXTURED_TEXCOORD_ARRAY_SIZE, GL_FLOAT, GL_FALSE, sizeof(struct MeshTextured), MESHTEXTURED_TEXCOORD_OFFSET);
}
