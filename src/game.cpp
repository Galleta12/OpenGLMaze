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

#include "Components.h"
#include "MainCamera.h"
#include "TrianguleFigure.h"
#include "CubeFigure.h"
#include "RayFigure.h"
#include "PlaneFigure.h"
#include "Player.h"
#include "Map.h"

//initialize static variables
int Game::Width = 0;
int Game::Height = 0;

bool Game::isRunning = false;
        
GLFWwindow* Game::window = nullptr;

Game::WhoISCamera Game::cameraViewState = Game::WhoISCamera::MAINCAMERA;

Shader *shaderProgram = nullptr;
Shader *lightShader = nullptr;
Camera *camera = nullptr;


VAO *lightVAO = nullptr;

VBO *lightVBO = nullptr;

EBO *lightEBO = nullptr;

Texture *rotateTex = nullptr;
Texture *planeTex = nullptr;


ModelMatrix *modelMatrix = nullptr;

ModelMatrix *lightModelMatrix = nullptr;

MainCamera* mainCamera;

Map* map;

Player* mainPlayer;

Manager manager;

auto &cameraOrthoEntity(manager.addEntity());
auto &planeEntity(manager.addEntity());
auto &triangle(manager.addEntity());
auto &triangleRotate(manager.addEntity());


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

	orthowViewWidht = width/2;
	orthowViewHeight = height/2;

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

auto& camerasWorld(manager.getGroup(Game::groupCameras));
auto& triangleWorld(manager.getGroup(Game::groupTriangle));
auto& collidersWorld(manager.getGroup(Game::groupColliders));
auto& orthoCamerasWorld(manager.getGroup(Game::groupCameraOrtho));
auto& planeWorld(manager.getGroup(Game::groupPlane));

void Game::handleEvents()
{

	CameraComponent *firstViewCamera = mainPlayer->getCamaraEntityPlayer();
    //ppointet ro the orthocamera
    if(glfwWindowShouldClose(window)){
        isRunning = false;
    }
	
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS){
		
		cameraViewState = WhoISCamera::MAINCAMERA;
		firstViewCamera->shouldDraw = false;
		mainCamera->getCameraComponent()->shouldDraw = true;
	}
	
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS){
		
		cameraViewState = WhoISCamera::FIRTPLAYERCAM;
		firstViewCamera->shouldDraw = true;
		mainCamera->getCameraComponent()->shouldDraw = false;
	}


}


void Game::update(float deltaTime)
{
    
	handleOrthoCameraLogic();
	manager.refresh();
    manager.update(deltaTime);
	

	
	TransformComponent *planeTranform = &planeEntity.getComponent<TransformComponent>(); 
	
	


	planeTranform->Scale(planeTranform->getMainFigureComponent()->scaleFactorFigure);
	


	physicsLoop(deltaTime);


}

void Game::display()
{
    // Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    
	glViewport(0, 0, Width, Height);
    // Specify the color of the background
	// Clean the back buffer and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    
	drawFirstViewPort();
	
	//second viewport
	glViewport(orthowViewWidht, orthowViewHeight, orthowViewWidht, orthowViewHeight);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT);
	drawSecondViewPort();


    // Swap the back buffer with the front buffer
	glfwSwapBuffers(window);
}

void Game::clean()
{

	// Delete all the objects we've created
	
	shaderProgram->Delete();
	lightVAO->Delete();
	lightVBO->Delete();
	lightEBO->Delete();
	lightShader->Delete();

	rotateTex->Delete();

    // Delete window before ending the program
	glfwDestroyWindow(window);
	window = NULL;
    // Terminate GLFW before ending the program
	
    glfwTerminate();
     std::cout << "Game closed" << std::endl;

}

void Game::physicsLoop(float deltaTime)
{

	//all of this must have a collider component
    for (int i=0; i < collidersWorld.size()-1; i++)
	{
        PhysicsComponent *physics1 = &collidersWorld[i]->getComponent<PhysicsComponent>();
        TransformComponent *tra1 = &collidersWorld[i]->getComponent<TransformComponent>();

        for(int j=i+1; j <collidersWorld.size();j++){
            PhysicsComponent *physics2 = &collidersWorld[j]->getComponent<PhysicsComponent>();
            TransformComponent *tra2 = &collidersWorld[j]->getComponent<TransformComponent>();
    
            //check collision
            float depth = std::numeric_limits<float>::infinity();; 
            Vector3D normalCollision;
            
            bool isIntersection = physics1->AABBCOLLISION(tra2,depth, normalCollision);  
        
			if(isIntersection){
                
                tra1->OnCollisionEnter(tra1,tra2,depth,normalCollision);
                tra2->OnCollisionEnter(tra2,tra1,depth,normalCollision);
				
                
            }

        
        }
    
    } 

}

void Game::setUpShaderAndBuffers()
{

    //generate the texture
	
	
	
	// Generates Shader object using shaders default.vert and default.frag
	shaderProgram = new Shader("default.vert", "default.frag");

	map = dynamic_cast<Map*>(&manager.addEntityClass<Map>(*shaderProgram));
	//brick tex
	// brickTex = new Texture("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    
    // brickTex->texUnit(*shaderProgram, "tex0", 0);
	
	//rotate tex
	rotateTex = new Texture("RotateTriangle.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    
    rotateTex->texUnit(*shaderProgram, "tex0", 0);
	
	
	//plane tex
	planeTex = new Texture("planks.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
    
    planeTex->texUnit(*shaderProgram, "tex0", 0);
	
	//the specular is create inside the plane class

	
	
	mainPlayer = dynamic_cast<Player*>(&manager.addEntityClass<Player>(*shaderProgram,*rotateTex));
	


	PlaneFigure *plane = &planeEntity.addComponent<PlaneFigure>(*shaderProgram,Vector3D(30.0f,1.0f,30.0f), *planeTex);
	planeEntity.addComponent<TransformComponent>(Vector3D(0.0f,0.0f,0.0f),true,plane);

	planeEntity.addGroup(groupPlane);




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

    

	lightModelMatrix = new ModelMatrix();
	lightModelMatrix->loadIdentity();
	lightModelMatrix->traslation(Vector3D(-3.0f, 2.3f, -1.0f));
	
	lightShader->use();


	lightShader->set_model_matrix(lightModelMatrix->getMatrix());
	lightShader->set_light_color(1.0f, 1.0f, 1.0f, 1.0f);
	
	shaderProgram->use();
	
	


	shaderProgram->set_light_color(1.0f, 1.0f, 1.0f, 1.0f);
	shaderProgram->set_light_position(-3.0f, -1.3f, 0.0f);


	mainCamera = dynamic_cast<MainCamera*>(&manager.addEntityClass<MainCamera>());

	
	//ortho camera
	cameraOrthoEntity.addComponent<CameraComponent>(Vector3D(1.0f,5.0f,1.0f));
    
    CameraComponent *orthoCam = &cameraOrthoEntity.getComponent<CameraComponent>();

    orthoCam->shouldDraw = true;
    cameraOrthoEntity.addGroup(groupCameraOrtho);
	
	float aspect =  static_cast<int>(orthowViewWidht/ orthowViewHeight);

    orthoCam->setLooKViewCamera(Vector3D(1.0f,5.0f,1.0f), Vector3D(0.0f,0.0f,0.0f), Vector3D::UP());

    orthoCam->setOrthoGraphicProjection(-7.0f* aspect, 7.0f * aspect, -7.0f, 7.0f, 0.00001f, 100.0f);





}

void Game::handleOrthoCameraLogic()
{
	
    TransformComponent *p = &mainPlayer->getComponent<TransformComponent>();

    
    
    Vector3D posPlayer(p->position.x,cameraOrthoEntity.getComponent<CameraComponent>().getViewMatrixPointer()->getVectorEye().y,p->position.z);
    
    cameraOrthoEntity.getComponent<CameraComponent>().getViewMatrixPointer()->setEyePos(posPlayer);



}

void Game::drawFirstViewPort()
{

	// Tells OpenGL which Shader Program we want to use
	shaderProgram->use();
	// Exports the camera Position to the Fragment Shader for specular lighting
	
	Vector3D pos = mainCamera->getCameraComponent()->eyePosition;

	shaderProgram->set_eye_position(pos.x, pos.y, pos.z);
	
	for(auto& c : camerasWorld){
       c->draw(*shaderProgram); 
    }
	
	for(auto& p : planeWorld){
       p->draw(*shaderProgram); 
    }
	
		
	for(auto& t : triangleWorld){
       t->draw(*shaderProgram); 
    }
	
	for(auto& co : collidersWorld){
       co->draw(*shaderProgram); 
    }
	
	
	// Tells OpenGL which Shader Program we want to use
	
	lightShader->use();
	
	// Export the camMatrix to the Vertex Shader of the light cube
	
	//camera->Matrix(*lightShader, "camMatrix");
	lightVAO->Bind();
	
	for(auto& c : camerasWorld){
        c->draw(*lightShader); 
    }
	
	// Bind the VAO so OpenGL knows to use it
	
	// Draw primitives, number of indices, datatype of indices, index of indices
	glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);


}

void Game::drawSecondViewPort()
{



	// Tells OpenGL which Shader Program we want to use
	shaderProgram->use();
	// Exports the camera Position to the Fragment Shader for specular lighting
	
	//maybe
	// Vector3D pos = mainCamera->getCameraComponent()->eyePosition;

	// shaderProgram->set_eye_position(pos.x, pos.y, pos.z);
	
	for(auto& o : orthoCamerasWorld){
        o->draw(*shaderProgram);
        
    }

	for(auto& p : planeWorld){
       p->draw(*shaderProgram); 
    }
	
		
	for(auto& t : triangleWorld){
       t->draw(*shaderProgram); 
    }
	
	for(auto& co : collidersWorld){
       co->draw(*shaderProgram); 
    }
	
	
	// Tells OpenGL which Shader Program we want to use
	
	lightShader->use();
	
	// Export the camMatrix to the Vertex Shader of the light cube
	
	//camera->Matrix(*lightShader, "camMatrix");
	lightVAO->Bind();
	
	for(auto& o : orthoCamerasWorld){
        o->draw(*lightShader);
        
    }
	
	// Bind the VAO so OpenGL knows to use it
	
	// Draw primitives, number of indices, datatype of indices, index of indices
	glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);






}
