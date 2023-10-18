#pragma once
#include "Vector3D.h"
#include "Point.h"
#include "Matrices.h"
#include <vector>
#include <memory>

#include "ECS.h"
#include "Components.h"

class TransformComponent;
class PhysicsComponent : public Component{

    public:
       
        bool isPlayer=false;
        
        bool canMove;
        
        PhysicsComponent(bool isMovable = true);
        ~PhysicsComponent();
        void init() override;
      
        bool AABBCOLLISION( const TransformComponent* p2,float& depth, Vector3D& normalCollision);


    private:
        


        TransformComponent *mTransformComponent;
        
        void ProjectAxis(const std::vector<Vector3D>& verticesList, Vector3D axis,float &min, float &max);

        Vector3D FindCenterMean(const std::vector<Vector3D*> vertices);

        std::vector<Vector3D> CalculateVertices(const Vector3D& position, const Vector3D& scale);

        std::vector<Vector3D> CalculateNormals(const std::vector<Vector3D>& vertices);

        void ProjectVertices(const std::vector<Vector3D>& vertices, const Vector3D& axis, float& min, float& max);
};