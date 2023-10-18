#include "Player.h"
#include "CubeFigure.h"
#include "RayFigure.h"
#include "RadToDegree.h"

#include <iostream>


Player::Player(Manager &mManager, Shader& shader, Texture &tex)
:Entity(mManager)
{
    

    CubeFigure *cube  = &Entity::addComponent<CubeFigure>(shader,Vector3D(1.0f,1.0f,1.0f),tex);
    
    ray  = &Entity::addComponent<RayFigure>(shader,Vector3D(1.0f,1.0f,1.0f),tex,Vector3D(0.050f,0.050f,2.0f) );
    
    
    
    
    Entity::addComponent<TransformComponent>(Vector3D(0.0f,0.0f,0.0f),true,cube);

    Entity::addComponent<PhysicsComponent>();   
    
    
    transformComponent = &Entity::getComponent<TransformComponent>();
    transformComponent->isPlayer = true;
    mPhysicsComponent = &Entity::getComponent<PhysicsComponent>();
    
    
    Entity::addGroup(Game::groupColliders);
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
}

void Player::handlePlayerMoves(float deltaTime)
{
    
    playerTraslation(deltaTime);
    playerRotation(deltaTime);

}

void Player::playerTraslation(float deltaTime)
{

    
    float adjustedSpeed = mSpeed * deltaTime;
    
    Vector3D orientation = transformComponent->OrientationVector.normalize();

    Vector3D keyDir(0.0f, 0.0f, 0.0f);

    if (glfwGetKey(Game::window, GLFW_KEY_UP) == GLFW_PRESS) {
        keyDir += Vector3D(0.0f, 0.0f, 1.0f);
    }

    if (glfwGetKey(Game::window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        keyDir += Vector3D(0.0f, 0.0f, -1.0f);
    }

    if (glfwGetKey(Game::window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        keyDir += Vector3D(-1.0f, 0.0f, 0.0f);
    }

    if (glfwGetKey(Game::window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        keyDir += Vector3D(1.0f, 0.0f, 0.0f);
    }

        
    
     transformComponent->position +=  keyDir * adjustedSpeed;
    

    
    
    ray->TraslateFigure(transformComponent->position);



}

//for now only rotation on the y axis
void Player::playerRotation(float deltaTime)
{

    
    
    
    
    
    if (glfwGetKey(Game::window, GLFW_KEY_Q) == GLFW_PRESS) {
        
        angleRotationY -= RadToDegree::PI * deltaTime;
        
        transformComponent->OrientationVector = Vector3D::Rotation(transformComponent->OrientationVector,Vector3D::UP(),angleRotationY);        
    
    }

    else if (glfwGetKey(Game::window, GLFW_KEY_E) == GLFW_PRESS) {
        
        angleRotationY += RadToDegree::PI * deltaTime;
        transformComponent->OrientationVector = Vector3D::Rotation(transformComponent->OrientationVector,Vector3D::UP(),angleRotationY);
    
    }
    
   
    transformComponent->RotationAboutAxis(Vector3D::UP(),angleRotationY);
     
    ray->RotationAboutAxisFigure(Vector3D::UP(),angleRotationY);
    


}

void Player::handleCamLogic(float deltaTime, float angleRot)
{

  

}


