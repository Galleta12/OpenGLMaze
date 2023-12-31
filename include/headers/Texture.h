#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<stb/stb_image.h>

#include"shaderClass.h"

class Texture
{
public:
	GLuint ID;
	GLenum type;
	//allow multiple texture on a shader
	GLuint unit; 
	
	Texture(const char* image, GLenum texType, GLuint slot, GLenum format, GLenum pixelType);

	//assig a texture unit to texture object
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Delete();
};
#endif