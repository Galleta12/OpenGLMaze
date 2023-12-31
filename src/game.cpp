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
#include "Light.h"

//initialize static variables
int Game::Width = 0;
int Game::Height = 0;

bool Game::isRunning = false;
        
GLFWwindow* Game::window = nullptr;

Game::WhoISCamera Game::cameraViewState = Game::WhoISCamera::MAINCAMERA;

Shader *shaderProgram = nullptr;
Shader *lightShader = nullptr;
Shader *lightShader2 = nullptr;

Texture *rotateTex = nullptr;
Texture *planeTex = nullptr;

MainCamera* mainCamera;

Map* map;

Player* mainPlayer;

LightSource* ligthSource1;

LightSource* ligthSource2;

Manager manager;

auto &cameraOrthoEntity(manager.addEntity());
auto &planeEntity(manager.addEntity());





//initialize glfw 
Game::Game()
{


	glfwInit();

	// opengl version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	// set glfw that we will use the open gl moder functiontions
		
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

	//load glad for using modern opengl functionalities
	gladLoadGL();
	

	//initial viewport
	glViewport(0, 0, width, height);

    isRunning = true;

    setUpShaderAndBuffers();
    setUpEntities();

}

//all the types that we are going to use
auto& camerasWorld(manager.getGroup(Game::groupCameras));
auto& triangleWorld(manager.getGroup(Game::groupTriangle));
auto& collidersWorld(manager.getGroup(Game::groupColliders));
auto& orthoCamerasWorld(manager.getGroup(Game::groupCameraOrtho));
auto& planeWorld(manager.getGroup(Game::groupPlane));
auto& lightsWorld(manager.getGroup(Game::groupLights));

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

	glEnable(GL_DEPTH_TEST);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
	glViewport(0, 0, Width, Height);

	
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
	
	lightShader->Delete();
	lightShader2->Delete();

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
	
	
	
	shaderProgram = new Shader("simple.vert", "simple.frag");

	map = dynamic_cast<Map*>(&manager.addEntityClass<Map>(*shaderProgram));

	//rotate tex
	rotateTex = new Texture("RotateTriangle.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    
    rotateTex->texUnit(*shaderProgram, "tex0", 0);
		
	//plane tex
	//the specular is set on the planfigure constuctor
	planeTex = new Texture("planks.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
    
    planeTex->texUnit(*shaderProgram, "tex0", 0);
	
	//player
	mainPlayer = dynamic_cast<Player*>(&manager.addEntityClass<Player>(*shaderProgram,*rotateTex));
	


	PlaneFigure *plane = &planeEntity.addComponent<PlaneFigure>(*shaderProgram,Vector3D(50.0f,1.0f,50.0f), *planeTex);
	planeEntity.addComponent<TransformComponent>(Vector3D(0.0f,0.0f,0.0f),true,plane);

	planeEntity.addGroup(groupPlane);




	// Shader for light cube
	lightShader = new Shader("light.vert", "light.frag");
	lightShader2 = new Shader("light2.vert", "light2.frag");
	// Generates Vertex Array Object and binds it
	//start light shader	
	//generate ligh class
	//LineSource light1 = dynamic_cast<LineSource*>(&manager.addEntityClass<LineSource>(*shaderProgram,*rotateTex));
	//manager.addEntityClass<LightSource>(*lightShader,Vector3D(-3.0f, 2.3f, -1.0f), Vector3D(1.0f, 1.0f, 1.0f), 1.0f);
	
	
	ligthSource1 = dynamic_cast<LightSource*>(&manager.addEntityClass<LightSource>(*lightShader,Vector3D(5.0f, 5.3f, -1.0f), Vector3D(1.0f, 1.0f, 1.0f), 1.0f,1));
	
	ligthSource2 = dynamic_cast<LightSource*>(&manager.addEntityClass<LightSource>(*lightShader2,Vector3D(5.0f, 2.3f, -1.0f), Vector3D(1.0f, 0.4f, 0.8f), 0.3f,2));




}



void Game::setUpEntities()
{

	//set up the initial light color and position on the shader
	//this can be improved
	shaderProgram->use();
	
	//the ligth color and position should be the same as the ligth color and position
	//of the light


	// shaderProgram->set_light_color(1.0f, 1.0f, 1.0f, 1.0f);
	// shaderProgram->set_light_position(-3.0f, -1.3f, 0.0f);



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

	// set the current shader
	shaderProgram->use();
	//use the camera pos for the specular lighthing
	Vector3D pos;
	if(cameraViewState == MAINCAMERA){

		pos = mainCamera->getCameraComponent()->getViewMatrixPointer()->getVectorEye();
	}
	else if (cameraViewState == FIRTPLAYERCAM){
		pos = mainPlayer->getCamaraEntityPlayer()->getViewMatrixPointer()->getVectorEye();
	}
	//Vector3D pos = mainCamera->getCameraComponent()->eyePosition;

	shaderProgram->set_eye_position(pos.x, pos.y, pos.z);
	
	setLighPosColorGlobalShader();
	setLightSpotLight();
	
	
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
	
	
	
	// opengl set the shader that we would use
	
	//we are already using the light on the light shader entity
	lightShader->use();
	
	// Export the camMatrix to the Vertex Shader of the light cube	
	for(auto& c : camerasWorld){
        c->draw(*lightShader); 
    }
	
	for(auto& l : lightsWorld){
       l->draw(*shaderProgram); 
    }
	
	lightShader2->use();
	
	// for drawing the second light
	for(auto& c : camerasWorld){
        c->draw(*lightShader); 
    }
	
	for(auto& l : lightsWorld){
       l->draw(*shaderProgram); 
    }





}

void Game::drawSecondViewPort()
{



	// Tells OpenGL which Shader Program we want to use
	shaderProgram->use();
	

	//apply global ambient



	setLighPosColorGlobalShader();
	setLightSpotLight();
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
	
	

	
	lightShader->use();
	
	for(auto& o : orthoCamerasWorld){
        o->draw(*lightShader);
        
    }

	for(auto& l : lightsWorld){
       l->draw(*shaderProgram); 
    }
	
	// lightShader2->use();
	
	// for(auto& o : orthoCamerasWorld){
    //     o->draw(*lightShader);
        
    // }

	// for(auto& l : lightsWorld){
    //    l->draw(*shaderProgram); 
    // }
	

}

void Game::setLighPosColorGlobalShader()
{
	Vector3D lighPos = ligthSource1->getPosition();
	Vector3D lighColor = ligthSource1->getColor();
	float lastrgbA = ligthSource1->getLastColorA();

	
	shaderProgram->set_light_color(lighColor.x, lighColor.y, lighColor.z, lastrgbA);
	
	shaderProgram->set_light_position(lighPos.x, lighPos.y, lighPos.z);

	shaderProgram->set_light_specular(0.20f);
	
	shaderProgram->set_ambient_light(0.50f);
	
	
	shaderProgram->set_square_a(0.05f);
	shaderProgram->set_square_b(0.01f);
}

void Game::setLightSpotLight()
{
	Vector3D lighPos = ligthSource2->getPosition();
	Vector3D lighColor = ligthSource2->getColor();
	float lastrgbA = ligthSource2->getLastColorA();

	
	shaderProgram->set_light_color2(lighColor.x, lighColor.y, lighColor.z, lastrgbA);
	
	shaderProgram->set_light_position2(lighPos.x, lighPos.y, lighPos.z);
	// controls how big the of the spot should be
	shaderProgram->set_outer_cone(0.70f);
	shaderProgram->set_inner_cone(0.75f);


	
}
