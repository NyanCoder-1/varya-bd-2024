#include "assets.h"
#include "graphics.h"
#include "stdlib.h"
#include <GLES3/gl3.h>
#include <stb_image.h>

struct Texture {
	GLuint texture;
	uint32_t width;
	uint32_t height;
};

texture_t textureCreateFromPngFile(const char *pngPath)
{
	uint32_t pngDataSize = 0;
	char* pngData = loadAsset(pngPath, &pngDataSize);
	texture_t texture = textureCreateFromPngInMemory(pngData, pngDataSize);
	free(pngData);
	return texture;
}

texture_t textureCreateFromPngInMemory(const char *pngData, const uint32_t pngDataSize)
{
	texture_t texture = (texture_t)malloc(sizeof(struct Texture));
	texture->texture = 0;
	glGenTextures(1, &texture->texture);
	glBindTexture(GL_TEXTURE_2D, texture->texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, channels;
	stbi_uc *imageBuffer = stbi_load_from_memory((const stbi_uc*)pngData, pngDataSize, &width, &height, &channels, 4);
	texture->width = width;
	texture->height = height;
	if (imageBuffer != NULL) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageBuffer);
	}
	stbi_image_free(imageBuffer);

	return texture;
}

void textureDestroy(texture_t *texture)
{
	if (texture) {
		if ((*texture)->texture)
			glDeleteTextures(1, &(*texture)->texture);
		(*texture)->texture = 0;
		(*texture)->width = 0;
		(*texture)->height = 0;
		free(*texture);
		*texture = NULL;
	}
}

void textureUse(texture_t texture)
{
	if (texture == NULL)
		return;
	glBindTexture(GL_TEXTURE_2D, texture->texture);
}
