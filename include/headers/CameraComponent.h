#pragma once

#include <vector>
#include <memory>
#include "ECS.h"
#include "Components.h"
#include "ShaderClass.h"
#include "Matrices.h"
#include "Vector3D.h"
#include "Point.h"

//the camera will have reference to the view and projection matrix
class CameraComponent : public Component{

    public:

       
        bool shouldDraw = false;
        
        //zoom this is the fov
        //this is a 90 degree fox, always in radians
        float zoom = 0.0f;
        //keep track of the position of the camera. this is in world space
        Vector3D eyePosition;
        //set up view and projectionMatrix        
        Vector3D orientation = Vector3D(0.0f,0.0f, -1.0f);
        
        //bool is orthographic
        
        bool isOrthoGraphic = false;
        
        CameraComponent(Vector3D _eyePosition);
        
        ~CameraComponent();

        void setLooKViewCamera(Vector3D eye, Vector3D center, Vector3D up);
        void setPerspectiveProjection(float fov, float _aspect, float _near, float _far);
        
   
        //we want on the draw set up the shaders
        void draw(Shader& shader) override;
        void update(float deltaTime) override; 
        //for the orthographic as well

    
        void setViewShader(Shader& shader);
        
        void setProjectionShader(Shader& shader);
        
        void setOrthoGraphicProjection(float _left, float _right, float _bottom, float _top, float _nearPlane, float _farPlane);
        

        // Return a pointer to the view matrix
        ViewMatrix* getViewMatrixPointer() {
            return mViewMatrix.get();
        }

        // Return a pointer to the projection matrix
        ProjectionMatrix* getProjectionMatrixPointer() {
            return mProjectionMatrix.get();
        }
      
    
    private:


        std::unique_ptr<ViewMatrix> mViewMatrix = std::make_unique<ViewMatrix>();
        std::unique_ptr<ProjectionMatrix> mProjectionMatrix = std::make_unique<ProjectionMatrix>();
        
};

