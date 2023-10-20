#include "Player.h"
#include "CubeFigure.h"
#include "RayFigure.h"
#include "RadToDegree.h"

#include <iostream>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

Player::Player(Manager &mManager, Shader& shader, Texture &tex)
:Entity(mManager)
{
    
    
    redtex = new Texture("red.png", GL_TEXTURE_2D, 0,  GL_RED, GL_UNSIGNED_BYTE);
    
    redtex->texUnit(shader, "tex0", 0);
    

    CubeFigure *cube  = &Entity::addComponent<CubeFigure>(shader,Vector3D(1.0f,1.0f,1.0f),tex);
        
    
    ray  = &Entity::addComponent<RayFigure>(shader,Vector3D(1.0f,1.0f,1.0f),*redtex,Vector3D(0.050f,0.050f,2.5f));
    
    
    
    
    Entity::addComponent<TransformComponent>(Vector3D(0.0f,0.6f,0.0f),true,cube);

    Entity::addComponent<PhysicsComponent>();   
    
    
    transformComponent = &Entity::getComponent<TransformComponent>();
    transformComponent->isPlayer = true;
    mPhysicsComponent = &Entity::getComponent<PhysicsComponent>();
    

    Entity::addGroup(Game::groupColliders);
    
    //for the camera
    //create a new entity
    auto &cam(mManager.addEntity());
    //add camera to the entity
    cam.addComponent<CameraComponent>(Vector3D(transformComponent->position.x,1.0f,transformComponent->position.z));
    //add a group
    cam.addGroup(Game::groupCameras);

    mFirsViewCamera = &cam.getComponent<CameraComponent>();

    setUpFirstViewCamera();

}

Player::~Player()
{
}

void Player::SetUpComponets()
{



}

void Player::update(float deltaTime)
{
    Entity::update(deltaTime);
    
    handlePlayerMoves(deltaTime);
}

void Player::draw(Shader &shader)
{
    Entity::draw(shader);
}

void Player::renderFirstViewCamera()
{
}

void Player::setUpFirstViewCamera()
{
       
    Vector3D initialCenter = mFirsViewCamera->eyePosition + Vector3D(0.0f,0.0f,-1.0f);
    
    
    mFirsViewCamera->setLooKViewCamera(mFirsViewCamera->eyePosition,initialCenter,Vector3D::UP());
    //for the shaders they are done on the draw using this data

    //for now the aspct ration is
    float aspect =  static_cast<float>(Game::Width / Game::Height);
    
    mFirsViewCamera->setPerspectiveProjection(RadToDegree::ToRadians(100.0f),aspect, 0.1f,100.0f);

}

void Player::handlePlayerMoves(float deltaTime)
{
    
    playerTraslation(deltaTime);
    playerRotation(deltaTime);


}

void Player::playerTraslation(float deltaTime)
{
    
    float adjustedSpeed = mSpeed * deltaTime;
    
    
    
    
    std::cout << "ortientation glm" << glm::to_string(newOrientation) << std::endl;
    std::cout << "my forward" << transformComponent->forward << std::endl;
    
    
    
    std::cout << "right view camera          " << mFirsViewCamera->getViewMatrixPointer()->getViewX()<< std::endl;
    std::cout << "forward view camera       " << mFirsViewCamera->getViewMatrixPointer()->getViewZ() << std::endl;
    
    Vector3D keyDir(0.0f, 0.0f, 0.0f);

    if (glfwGetKey(Game::window, GLFW_KEY_UP) == GLFW_PRESS) {
        keyDir += Vector3D(0.0f, 0.0f, -1.0f);
    }

    if (glfwGetKey(Game::window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        keyDir += Vector3D(0.0f, 0.0f, 1.0f);

    }

    if (glfwGetKey(Game::window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        keyDir += Vector3D(-1.0f, 0.0f, 0.0f);

    }

    if (glfwGetKey(Game::window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        keyDir += Vector3D(1.0f, 0.0f, 0.0f);

    }


    float delZ = keyDir.z * adjustedSpeed;
    float delX = keyDir.x * adjustedSpeed;
     
    
     transformComponent->position +=  mFirsViewCamera->getViewMatrixPointer()->getViewZ() * delZ  +  mFirsViewCamera->getViewMatrixPointer()->getViewX() *delX;
    
    
    
    
    
    ray->TraslateFigure(transformComponent->position + Vector3D(0.0f,0.3f,0.0f));
    
    //mFirsViewCamera->getViewMatrixPointer()->walkYAxis(keyDir.x * adjustedSpeed, keyDir.z * adjustedSpeed);
    mFirsViewCamera->getViewMatrixPointer()->setEyePos(transformComponent->position +  Vector3D::UP());



}

//for now only rotation on the y axis
void Player::playerRotation(float deltaTime)
{

    
    float angleRot = RadToDegree::PI * deltaTime;
    
    
    if (glfwGetKey(Game::window, GLFW_KEY_Q) == GLFW_PRESS) {
        
        angleRotationY -= RadToDegree::PI * deltaTime;
        
        mFirsViewCamera->getViewMatrixPointer()->TurnFirstCamView(angleRot);

        transformComponent->forward = Vector3D::RotateVectorAboutAxis(transformComponent->forward,Vector3D::UP(),angleRot);
        transformComponent->right = Vector3D::RotateVectorAboutAxis(transformComponent->right,Vector3D::UP(),angleRot);
         
        newOrientation = glm::rotate(newOrientation, glm::radians(angleRot), glm::vec3(0.0f, 1.0f, 0.0f));
    
    }

    else if (glfwGetKey(Game::window, GLFW_KEY_E) == GLFW_PRESS) {
        
        angleRotationY += RadToDegree::PI * deltaTime;
        mFirsViewCamera->getViewMatrixPointer()->TurnFirstCamView(-angleRot);

        transformComponent->forward = Vector3D::RotateVectorAboutAxis(transformComponent->forward,Vector3D::UP(),-angleRot);
        transformComponent->right = Vector3D::RotateVectorAboutAxis(transformComponent->right,Vector3D::UP(),-angleRot);
        
        newOrientation = glm::rotate(newOrientation, glm::radians(-angleRot), glm::vec3(0.0f, 1.0f, 0.0f));



    }
    
    
//    transformComponent->forward.x = newOrientation.x;
//    transformComponent->forward.y = newOrientation.y;
//    transformComponent->forward.z = newOrientation.z;
   
   //std::cout << "forward" << transformComponent->forward << std::endl;
   //std::cout << "ortientation glm" << glm::to_string(newOrientation) << std::endl;



    transformComponent->RotationAboutAxis(Vector3D::UP(),angleRotationY);
     
    ray->RotationAboutAxisFigure(Vector3D::UP(),angleRotationY);
    


}

void Player::handleCamLogic(float deltaTime, float angleRot)
{

  

}


