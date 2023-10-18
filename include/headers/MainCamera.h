#pragma once

#include "Game.h"

#include "ECS.h"
#include "Components.h"

#include "Matrices.h"
#include "Vector3D.h"
#include "Point.h"

//the main camera instance will be a perspective by default
class MainCamera : public Entity{

    public:
        MainCamera(Manager& mManager);
        
        ~MainCamera();
        
        void update(float deltaTime) override;
        
        void draw(Shader &shader) override;
        
        void saveComponents();

        
        CameraComponent* getCameraComponent(){
            return mCameraComponent;
        }

    private:


        CameraComponent * mCameraComponent;

        bool firstClick = true;
        
        float cameraSpeed = 1.0f;
        float sensitivity = 100.0f;
        
        void RotationCamera(float deltaTime);

        void ZoomCamera(float deltaTime);

        void ApplyNewPosition(float deltaTime);

        void Inputs(float deltaTime);

};
