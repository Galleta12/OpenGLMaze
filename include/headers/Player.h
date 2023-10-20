#pragma once
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "ECS.h"
#include "Components.h"
#include "ShaderClass.h"
#include "Vector3D.h"
#include "Texture.h"


class Player: public Entity{

    public:
        Player(Manager& mManager, Shader& shader, Texture &tex);
        ~Player();

        void SetUpComponets();

        //update of the player
        void update(float deltaTime) override;
        
        
        void draw(Shader &shader) override;

        void renderFirstViewCamera();

        CameraComponent *getCamaraEntityPlayer(){
            return mFirsViewCamera;
        }

 

    private:
        
        float angleRotationY=0.0f;
        
        float mSpeed = 5.0f;

        Texture *redtex = nullptr;

        Vector3D mDirection;
        Vector3D mDirectionKey;
        TransformComponent *transformComponent;
        RayFigure *ray;
        CameraComponent *mFirsViewCamera;
        
        PhysicsComponent *mPhysicsComponent;
        void setUpFirstViewCamera();
       
        void handlePlayerMoves(float deltaTime);
        void playerTraslation(float deltaTime);
        void playerRotation(float deltaTime);
        void playerPhysicsLoop();
        void handleCamLogic(float deltaTime, float angleRot);
        


};