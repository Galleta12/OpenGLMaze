#include"Texture.h"



Texture::Texture(const char* image, GLenum texType, GLuint slot, GLenum format, GLenum pixelType)
{
	// Assigns the type of the texture to the texture object
	
	type = texType;

	// Stores the width, height, and the number of color channels of the image
	int widthImg, heightImg, numColCh;
	//since stb store the coordinates from top to buttom and gl from bottom to top
	stbi_set_flip_vertically_on_load(true);
	//store the image in bytes
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	//create an opengl gl texture
	glGenTextures(1, &ID);
	
	// assign it to a texture unit (slot)
	//add multiple texture
	glActiveTexture(GL_TEXTURE0 + slot);
	
	unit = slot;
	glBindTexture(texType, ID);

	
	//paramters for rendering the image
	//this is based if we want it smaller or not
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// configure for the tex if it allow repetition
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	
	// assign image to open gl object
	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	//generate mipmax of the texture array
	glGenerateMipmap(texType);

	// free the image data
	stbi_image_free(bytes);

	// Unbinds the OpenGL Texture to dont be modified accidentally
	glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	// this is saved on the shader with the name of the texture
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	//active shader for setting up the values
	shader.use();
	// set the values on the unifor shader variable
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}