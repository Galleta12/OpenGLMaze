#include "Game.h"
#include <iostream>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"
#include "Matrices.h"
#include "Vector3D.h"


//initialize static variables
int Game::Width = 0;
int Game::Height = 0;

bool Game::isRunning = false;
        
GLFWwindow* Game::window = nullptr;

Shader *shaderProgram = nullptr;
Shader *lightShader = nullptr;
Camera *camera = nullptr;
VAO *VAO1 = nullptr;
VBO *VBO1 = nullptr;
EBO *EBO1 = nullptr;

VAO *lightVAO = nullptr;

VBO *lightVBO = nullptr;

EBO *lightEBO = nullptr;

Texture *brickTex = nullptr;

ModelMatrix *modelMatrix = nullptr;


//for now figures
// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2, // Bottom side
	0, 2, 3, // Bottom side
	4, 6, 5, // Left side
	7, 9, 8, // Non-facing side
	10, 12, 11, // Right side
	13, 15, 14 // Facing side
};

GLfloat lightVertices[] =
{ //     COORDINATES     //
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};









//initialize glfw 
Game::Game()
{


    // Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}

Game::~Game()
{
}

void Game::init(const char *title, int posX, int posY, int width, int height, bool fullscreen)
{

    Width = width;
    Height = height;

    // Create a GLFWwindow object of 1500 by 750 pixels, naming it "YoutubeOpenGL"
	window = glfwCreateWindow(Width, height, title, NULL, NULL);
    // Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		//we faile to create
        
        return;
	}

    //start opegl
    // Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);

    isRunning = true;

    setUpShaderAndBuffers();
    setUpEntities();

}

void Game::handleEvents()
{

    if(glfwWindowShouldClose(window)){
        isRunning = false;
    }

}

void Game::update(float deltaTime)
{
    
	// Handles camera inputs
	camera->Inputs(window, deltaTime);
	// Updates and exports the camera matrix to the Vertex Shader
	camera->updateMatrix(45.0f, 0.1f, 100.0f);


}

void Game::display()
{
    // Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, Width, Height);
    // Specify the color of the background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Clean the back buffer and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Tells OpenGL which Shader Program we want to use
	shaderProgram->Activate();
	// Exports the camera Position to the Fragment Shader for specular lighting
	glUniform3f(glGetUniformLocation(shaderProgram->ID, "camPos"), camera->Position.x, camera->Position.y, camera->Position.z);
	// Export the camMatrix to the Vertex Shader of the pyramid
	camera->Matrix(*shaderProgram, "camMatrix");
	// Binds texture so that is appears in rendering
	brickTex->Bind();
		// Bind the VAO so OpenGL knows to use it
	VAO1->Bind();
	// Draw primitives, number of indices, datatype of indices, index of indices
	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

	// Tells OpenGL which Shader Program we want to use
	lightShader->Activate();
	// Export the camMatrix to the Vertex Shader of the light cube
	camera->Matrix(*lightShader, "camMatrix");
	// Bind the VAO so OpenGL knows to use it
	lightVAO->Bind();
	// Draw primitives, number of indices, datatype of indices, index of indices
	glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);


    // Swap the back buffer with the front buffer
	glfwSwapBuffers(window);
}

void Game::clean()
{

	// Delete all the objects we've created
	VAO1->Delete();
	VBO1->Delete();
	EBO1->Delete();
	brickTex->Delete();
	shaderProgram->Delete();
	lightVAO->Delete();
	lightVBO->Delete();
	lightEBO->Delete();
	lightShader->Delete();


    // Delete window before ending the program
	glfwDestroyWindow(window);
	window = NULL;
    // Terminate GLFW before ending the program
	
    glfwTerminate();
     std::cout << "Game closed" << std::endl;

}



void Game::setUpShaderAndBuffers()
{

    
	// Generates Shader object using shaders default.vert and default.frag
	shaderProgram = new Shader("default.vert", "default.frag");
	// Generates Vertex Array Object and binds it
	VAO1 = new VAO();
	
    VAO1->Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO1 = new VBO(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO1 = new EBO(indices, sizeof(indices));
	// Links VBO attributes such as coordinates and colors to VAO
	VAO1->LinkAttrib(*VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO1->LinkAttrib(*VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1->LinkAttrib(*VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1->LinkAttrib(*VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1->Unbind();
	VBO1->Unbind();
	EBO1->Unbind();


	// Shader for light cube
	lightShader = new Shader("light.vert", "light.frag");
	// Generates Vertex Array Object and binds it
	lightVAO = new VAO;
	lightVAO->Bind();
	// Generates Vertex Buffer Object and links it to vertices
	lightVBO = new VBO(lightVertices, sizeof(lightVertices));
	// Generates Element Buffer Object and links it to indices
	lightEBO = new EBO(lightIndices, sizeof(lightIndices));
	// Links VBO attributes such as coordinates and colors to VAO
	lightVAO->LinkAttrib(*lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	// Unbind all to prevent accidentally modifying them
	lightVAO->Unbind();
	lightVBO->Unbind();
	lightEBO->Unbind();


}



void Game::setUpEntities()
{

    

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	
	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

	modelMatrix = new ModelMatrix();

	modelMatrix->loadIdentity();
	modelMatrix->traslation(Vector3D(0.0f, 0.0f, 0.0f));
	
	


	
	lightShader->Activate();
	
	glUniformMatrix4fv(glGetUniformLocation(lightShader->ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader->ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	
	shaderProgram->Activate();
	
	//glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	shaderProgram->set_model_matrix(modelMatrix->getMatrix());
	
	glUniform4f(glGetUniformLocation(shaderProgram->ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram->ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);



	/*
	* I'm doing this relative path thing in order to centralize all the resources into one folder and not
	* duplicate them between tutorial folders. You can just copy paste the resources from the 'Resources'
	* folder and then give a relative path from this folder to whatever resource you want to get to.
	* Also note that this requires C++17, so go to Project Properties, C/C++, Language, and select C++17
	*/
	// std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
	// std::string texPath = "/Resources/YoutubeOpenGL 7 - Going 3D/";

	// Texture
	brickTex = new Texture("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	brickTex->texUnit(*shaderProgram, "tex0", 0);



    //here maybe??
    
	



    //for the camera
    	// Creates camera object
	camera = new Camera(Width, Height, glm::vec3(0.0f, 0.0f, 2.0f));
}
