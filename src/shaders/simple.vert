#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;
// Texture Coordinates
layout (location = 2) in vec2 aTex;
// Normals (not necessarily normalized)
layout (location = 3) in vec3 aNormal;


//out puts for the fragment
out vec3 color;

out vec2 uv_coordinates_tex;

out vec3 Normal;

out vec3 position;

// Imports of the matrix
uniform mat4 u_projection_matrix;
// Imports the model matrix from 
uniform mat4 model;

//Import view matrix
uniform mat4 u_view_matrix;

void main()
{
	// calculates current position in global space
	vec3 global_position= vec3(model * vec4(aPos, 1.0f));

	//eye coordinates
	position = vec3(u_view_matrix *vec4(global_position, 1.0f));
	
	
	// Outputs the positions/coordinates of all vertices
	//in clip space
	gl_Position = u_projection_matrix * vec4(position, 1.0);

	// Assigns the colors from the vertex data
	color = aColor;
	// Assigns the texture coordinates from from the vertex data to the uv_coordiantes
	uv_coordinates_tex = aTex;
	// assig the normal to the normal for the fragment shader
	Normal = vec3(model * vec4(aNormal, 1.0f));
}