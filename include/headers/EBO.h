#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class EBO
{
public:
	GLuint ID;
	//generation of elements  buffer with link to the indices array
	EBO(GLuint* indices, GLsizeiptr size);

	
	void Bind();
	
	void Unbind();
	
	void Delete();
};

#endif