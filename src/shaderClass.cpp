#include"shaderClass.h"

// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

// Constructor that build the Shader Program from 2 different shaders
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// Read vertexFile and fragmentFile and store the strings
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// Convert the shader source strings into character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);
	// Checks if Shader compiled succesfully
	compileErrors(vertexShader, "VERTEX");

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);
	// Checks if Shader compiled succesfully
	compileErrors(fragmentShader, "FRAGMENT");

	// Create Shader Program Object and get its reference
	ID = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(ID);
	// Checks if Shaders linked succesfully
	compileErrors(ID, "PROGRAM");

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



	//save the variables

	modelMatrixLoc = glGetUniformLocation(ID, "model");
	
    viewMatrixLoc = glGetUniformLocation(ID, "u_view_matrix");

	projectionMatrixLoc = glGetUniformLocation(ID, "u_projection_matrix");

	eyePosLoc = glGetUniformLocation(ID, "u_eye_position");
 
}

// Activates the Shader Program
void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::use()
{
}

// Deletes the Shader Program
void Shader::Delete()
{
	glDeleteProgram(ID);
}

void Shader::set_model_matrix(const std::vector<GLfloat> matrix_array)
{
    
    GLfloat* model = vectorToArray(matrix_array);
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_TRUE, model);
}


void Shader::set_view_matrix(const std::vector<GLfloat> matrix_array)
{
    GLfloat* model = vectorToArray(matrix_array);
    glUniformMatrix4fv(viewMatrixLoc, 1, GL_TRUE, model);
}

void Shader::set_projection_matrix(const std::vector<GLfloat> matrix_array)
{
    GLfloat* model = vectorToArray(matrix_array);
    glUniformMatrix4fv(projectionMatrixLoc, 1, GL_TRUE, model);
}


void Shader::set_position_attribute(const std::vector<GLfloat> vertex_array)
{
    GLfloat* vertex = vectorToArray(vertex_array);
    glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, 0, vertex);
}

void Shader::set_normal_attribute(const std::vector<GLfloat> vertex_array)
{
    GLfloat* vertex = vectorToArray(vertex_array);
    glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 0, vertex);
}

void Shader::set_eye_position(float x, float y, float z)
{
    glUniform3f(eyePosLoc, x, y, z);
}

void Shader::set_light_position(float x, float y, float z)
{
    glUniform4f(lightPosLoc, x, y, z, 1.0);
}

void Shader::set_light_diffuse(float red, float green, float blue)
{
    glUniform4f(lightDiffuseLoc, red, green, blue, 1.0);
}
void Shader::set_light_specular(float red, float green, float blue)
{
    glUniform4f(lightSpecularLoc, red, green, blue, 1.0);
}

void Shader::set_material_diffuse(float red, float green, float blue)
{
    glUniform4f(materialDiffuseLoc, red, green, blue, 1.0);
}
void Shader::set_material_specular(float red, float green, float blue)
{
    glUniform4f(materialSpecularLoc, red, green, blue, 1.0);
}

void Shader::set_material_shininess(float shininess)
{
    glUniform1f(materialShininessLoc,shininess);
}

void Shader::set_view_matrixGLM(const glm::mat4 &viewMatrix)
{
    
	glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

}


void Shader::set_Projection_matrixGLM(const glm::mat4 &viewMatrix)
{
	glUniformMatrix4fv(projectionMatrixLoc, 1, GL_FALSE,glm::value_ptr(viewMatrix));
}




// Checks if the different Shaders have compiled properly
void Shader::compileErrors(unsigned int shader, const char* type)
{
	// Stores status of compilation
	GLint hasCompiled;
	// Character array to store error message in
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}


template <typename T>
inline float *Shader::vectorToArray(const std::vector<T> &vector)
{
    // Create a new array with the same size as the vector
    float* array = new float[vector.size()];

    // Copy the elements from the vector to the array
    for (size_t i = 0; i < vector.size(); ++i) {
        array[i] = static_cast<float>(vector[i]);
    }

    return array;
}
