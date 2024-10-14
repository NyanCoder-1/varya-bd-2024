#include "graphics.h"
// #include <cglm/cglm.h>
#include <GLES3/gl3.h>
#include <stdlib.h>

struct Mesh {
	GLuint vertexArrayObject;
	GLuint vertexBuffer;
	GLuint indexBuffer;
	uint32_t indexCount;
	// mat4 matrixModel;
};

mesh_t meshCreate(shader_t shader, void (*applyAttributesFn)(shader_t), const void *vertexData, const uint32_t vertexDataSize, const uint16_t *indicesData, const uint32_t indicesDataSize)
{
	GLuint vertexArrayObject;
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);
	GLuint vertexBuffer = 0;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertexData, GL_STATIC_DRAW);
	GLuint indexBuffer = 0;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesDataSize, indicesData, GL_STATIC_DRAW);
	shaderUse(shader);
	applyAttributesFn(shader);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	mesh_t mesh = (mesh_t)malloc(sizeof(struct Mesh));
	mesh->vertexArrayObject = vertexArrayObject;
	mesh->vertexBuffer = vertexBuffer;
	mesh->indexBuffer = indexBuffer;
	mesh->indexCount = indicesDataSize / sizeof(uint16_t);
	return mesh;
}

void meshDestroy(mesh_t *mesh)
{
	if (mesh) {
		if ((*mesh)->vertexBuffer) {
			glDeleteBuffers(1, &(*mesh)->vertexBuffer);
			(*mesh)->vertexBuffer = 0;
		}
		if ((*mesh)->indexBuffer) {
			glDeleteBuffers(1, &(*mesh)->indexBuffer);
			(*mesh)->indexBuffer = 0;
		}
		(*mesh)->indexCount = 0;
		free(*mesh);
		*mesh = NULL;
	}
}

void meshUpdateVertices(mesh_t mesh, const void *vertexData, const uint32_t vertexDataSize)
{
	if (!mesh)
		return;
	
	glBindVertexArray(mesh->vertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertexData, GL_STATIC_DRAW);
}

void meshDraw(mesh_t mesh)
{
	if (!mesh)
		return;

	glBindVertexArray(mesh->vertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_SHORT, 0);
}
