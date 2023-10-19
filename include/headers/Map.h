#pragma once
#include <vector>
#include "Vector3D.h"
#include "Matrices.h"

#include "ECS.h"
#include "Components.h"
#include "ShaderClass.h"
class CubeFigure;
class PhysicsComponent;
class TransformComponent;

class Map : public Entity{

        
    public:
        Map(Manager &mManager, Shader &shader);
        
        ~Map();


    
        void update(float deltaTime) override;

    private:

        Shader* shader;
        void setUpTexture(Shader &shader);
   
        
        void SetUpMapX(Manager &mManager);
        void GenerateUnRotatedWall(float row, float col,Manager &mManager);
        void GenerateRotatedWall(float row, float col,Manager &mManager);


        float tmpAngle = 0.0f;
        std::vector<Entity*> objects;

};