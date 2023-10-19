#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

class VAO
{
public:
	GLuint ID;
	//generation of a vertex array id

	VAO();

	// Links a VBO Attribute such as a position or color to the VAO
	//link the position color and texture to the vertex array object
	//this is based on the vertex buffer object

	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void Bind();
	void Unbind();
	void Delete();
};

#endif