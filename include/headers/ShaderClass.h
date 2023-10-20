#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>
#include<vector>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>



class Shader
{
public:
	// Reference ID of the Shader Program
	GLuint ID;
	// Constructor that build the Shader Program from 2 different shaders
	Shader(const char* vertexFile, const char* fragmentFile);

	
	//use shader
	void use();
	// Deletes the Shader Program
	
	void Delete();

	void set_model_matrix(const std::vector<GLfloat> matrix_array);
	void set_view_matrix(const std::vector<GLfloat> matrix_array);
    void set_projection_matrix(const std::vector<GLfloat> matrix_array);

	        
    void set_position_attribute(const std::vector<GLfloat> vertex_array);
    
	void set_normal_attribute(const std::vector<GLfloat> vertex_array);
        

    void set_light_position(float x, float y, float z);
    
    void set_light_position2(float x, float y, float z);
    
    void set_light_color(float x, float y, float z, float w);
    
    void set_light_color2(float x, float y, float z, float w);
        
    void set_light_diffuse(float red, float green, float blue);
        
    void set_material_diffuse(float red, float green, float blue);
         
    void set_eye_position(float x, float y, float z);

    void set_light_specular(float red, float green, float blue);

    void set_material_specular(float red, float green, float blue);
       
    void set_material_shininess(float shininess);
   
    void set_global_ambient(float ambient);
    
    void set_ambient_light(float ambient);
    
    
    void set_square_a(float a);
    void set_square_b(float b);

  


private:
	

    GLuint positionLoc;
    GLuint normalLoc;
    GLuint modelMatrixLoc;
    
    GLuint lightPosLoc;
    
    GLuint lightPos2Loc;
    
    GLuint lightColorLoc;
    
    GLuint lightColor2Loc;
    
    GLuint lightDiffuseLoc;
    
    GLuint materialDiffuseLoc; 
    
    GLuint eyePosLoc;
    
    GLuint lightSpecularLoc;
    
    GLuint materialSpecularLoc;  
    
    
    GLuint viewMatrixLoc;
    
    GLuint projectionMatrixLoc;
    
    GLuint materialShininessLoc;


    GLuint globalAmbientLoc;
    GLuint ambientLightLoc;
    
    GLuint squareConstantAmbientALoc;
    
    GLuint squareConstantAmbientBLoc;

	
	





	
	
	// Checks if the different Shaders have compiled properly
	void compileErrors(unsigned int shader, const char* type);


	template <typename T>
    float* vectorToArray(const std::vector<T>& vector);
};


#endif

