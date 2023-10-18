#include "Physics.h"


PhysicsComponent::PhysicsComponent(bool isMovable)
{
    canMove = isMovable;
}


PhysicsComponent::~PhysicsComponent()
{


}


void PhysicsComponent::init()
{
    mTransformComponent = &entity->getComponent<TransformComponent>();
}


bool PhysicsComponent::AABBCOLLISION(const TransformComponent *p2, float &depth, Vector3D &normalCollision)
{
   if(canMove == false && p2->entity->getComponent<PhysicsComponent>().canMove == false) return false;
    // std::cout << "vecto pos1 " << mTransformComponent->position << mTransformComponent->getMainFigureComponent()->scaleFactorFigure << std::endl;
    // std::cout << "vecto pos2 " << p2->position << p2->getMainFigureComponent()->scaleFactorFigure << std::endl;
    
    // Get the AABB boundaries for the first object
    Vector3D minA = mTransformComponent->position - (mTransformComponent->getMainFigureComponent()->scaleFactorFigure / 2.0f);
    Vector3D maxA = mTransformComponent->position + (mTransformComponent->getMainFigureComponent()->scaleFactorFigure / 2.0f);

    // Get the AABB boundaries for the second object
    Vector3D minB = p2->position - (p2->getMainFigureComponent()->scaleFactorFigure / 2.0f);
    Vector3D maxB = p2->position + (p2->getMainFigureComponent()->scaleFactorFigure / 2.0f);

    // Check for overlap in all dimensions (x, y, z)
    bool overlapX = (maxA.x >= minB.x) && (minA.x <= maxB.x);
    bool overlapY = (maxA.y >= minB.y) && (minA.y <= maxB.y);
    bool overlapZ = (maxA.z >= minB.z) && (minA.z <= maxB.z);

    // If there's overlap in all dimensions, a collision has occurred
    if (overlapX && overlapY && overlapZ) {
        // Calculate penetration depth (minimum overlap)
        float overlapXDepth = std::min(maxA.x - minB.x, maxB.x - minA.x);
        float overlapYDepth = std::min(maxA.y - minB.y, maxB.y - minA.y);
        float overlapZDepth = std::min(maxA.z - minB.z, maxB.z - minA.z);


        if (overlapXDepth <= overlapYDepth && overlapXDepth <= overlapZDepth) {
            normalCollision.x = (maxA.x - minB.x < maxB.x - minA.x) ? 1.0f : -1.0f;
        } else if (overlapYDepth <= overlapXDepth && overlapYDepth <= overlapZDepth) {
            normalCollision.y = (maxA.y - minB.y < maxB.y - minA.y) ? 1.0f : -1.0f;
        } else {
            normalCollision.z = (maxA.z - minB.z < maxB.z - minA.z) ? 1.0f : -1.0f;
        }
        
        
        // Find the smallest overlap depth
        depth = std::min(overlapXDepth, std::min(overlapYDepth, overlapZDepth));

       

        return true; // Collision detected
    }

    return false; 


}
