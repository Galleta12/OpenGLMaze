#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>


#include "Game.h"


const unsigned int width = 1200;
const unsigned int height = 800;


Game *game = nullptr;


int main()
{




	game = new Game();
	game->init("Game 3D", 0,0,width,height,false);


	
	double lastFrame = glfwGetTime();

	// Main while loop
	while (game->isRunning)
	{
		
		
		double currentFrame = glfwGetTime();
    	float deltaTime = static_cast<float>(currentFrame - lastFrame);
    	lastFrame = currentFrame;
		
		game->handleEvents();
		game->update(deltaTime);
		game->display();


	
		// Take care of all GLFW events
		glfwPollEvents();
	}


	game->clean();



	return 0;
}