#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 model;


uniform mat4 u_projection_matrix;

uniform mat4 u_view_matrix;


void main()
{
	
	
	gl_Position =  u_projection_matrix * u_view_matrix  * model * vec4(aPos, 1.0f);
}