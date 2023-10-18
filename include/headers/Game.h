#pragma once
#include <memory>
#include<glad/glad.h>
#include<GLFW/glfw3.h>


class Game{

    public:

        //for adding groups labels, all entities and components will have acces to this
        enum GroupLabels : std::size_t
        {
            groupColliders,
            groupCameras,
            groupCameraOrtho,
            groupTriangle
        };


        static enum WhoISCamera{
            MAINCAMERA,
            FIRTPLAYERCAM,
            OrthoCam
        };

        static WhoISCamera cameraViewState;
        
        static int Width, Height;
        static bool isRunning;
        static GLFWwindow* window;
   
        Game();
        ~Game();

        void init(const char* title, int posX, int posY, int width, int height, bool fullscreen);
          
        void handleEvents();

        void update(float deltaTime);

          //display of the boxes
        void display();
    
        void clean();
        //check if the game is running
        bool running() { return isRunning; }


        int orthowViewWidht, orthowViewHeight=0;

    private:


        void physicsLoop(float deltaTime);
        void setUpShaderAndBuffers();
        void setUpEntities();
        void handleOrthoCameraLogic();
        void drawFirstViewPort();
        void drawSecondViewPort();
        


};
