#include "assets.h"
#include "graphics.h"
#include <GLES3/gl3.h>
#include <stdio.h>
#include <stdlib.h>

struct Shader {
	GLuint program;
};

shader_t shaderCreateFromFile(const char *vertexShaderPath, const char *fragmentShaderPath)
{
	uint32_t vertexShaderSourceSize = 0;
	char* vertexShaderSource = loadAsset(vertexShaderPath, &vertexShaderSourceSize);
	uint32_t fragmentShaderSourceSize = 0;
	char* fragmentShaderSource = loadAsset(fragmentShaderPath, &fragmentShaderSourceSize);

	shader_t shader = shaderCreateFromMemory(vertexShaderSource, vertexShaderSourceSize, fragmentShaderSource, fragmentShaderSourceSize);
	free(vertexShaderSource);
	free(fragmentShaderSource);
	return shader;
}

GLuint createShaderObject(const char* shaderSource, int shaderType)
{
	// Create shader
	GLuint shader = glCreateShader(shaderType);
	// Attach shader source
	glShaderSource(shader, 1, &shaderSource, NULL);
	// Compile shader
	glCompileShader(shader);
	// Check for errors
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		// Print error
		GLint maxLength	= 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
		GLchar errorLog[maxLength];
		glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
		glDeleteShader(shader);
		fprintf(stderr, "%s\n", &errorLog[0]);
	}
	return shader;
}

shader_t shaderCreateFromMemory(const char *vertexShaderSource, const uint32_t vertexShaderSourceSize, const char *fragmentShaderSource, const uint32_t fragmentShaderSourceSize)
{
	// Create shader program
	GLuint program = glCreateProgram();
	// Create shaders
	GLuint vShader = createShaderObject(vertexShaderSource, GL_VERTEX_SHADER);
	GLuint fShader = createShaderObject(fragmentShaderSource, GL_FRAGMENT_SHADER);
	// Attach shaders
	glAttachShader(program, vShader);
	glAttachShader(program, fShader);
	// Link program
	glLinkProgram(program);
	// Predelete shader objects, so they automatically get deleted on glDeleteProgram
	glDeleteShader(vShader);
	glDeleteShader(fShader);

	// Create a wrapper object
	shader_t shader = (shader_t)malloc(sizeof(struct Shader));
	shader->program = program;
	return shader;
}

void shaderDestroy(shader_t *shader)
{
	if (shader) {
		if ((*shader)->program) {
			glDeleteProgram((*shader)->program);
			(*shader)->program = 0;
		}
		free(*shader);
		*shader = NULL;
	}
}

GLuint shaderGetProgram(shader_t shader)
{
	return shader ? shader->program : 0;
}

void shaderUse(shader_t shader)
{
	if (shader)
		glUseProgram(shader->program);
}
