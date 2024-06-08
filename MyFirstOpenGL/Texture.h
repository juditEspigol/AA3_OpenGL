#pragma once
#include <GL/glew.h>
#include <stb_image.h>

class Texture
{
private: 

	GLuint textureMode;

	int width, height, nrChannels;
	unsigned char* textureInfo;

	void InitTexture(); 

public:

	int textureIndex;

	Texture(const char* _filePath, GLuint _textureMode, int _textureIndex);
};