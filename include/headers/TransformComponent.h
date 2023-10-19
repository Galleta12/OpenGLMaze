#pragma once
#include <vector>
#include <memory>

#include "Game.h"
#include "ECS.h"
#include "Components.h"

#include "Vector3D.h"
#include "Point.h"
#include "Matrices.h"
#include "ShaderClass.h"
#include "Texture.h"

class FigureComponent;
class TrianguleFigure;
class CubeFigure;
class RayFigure;
class PlaneFigure;
class TransformComponent : public Component{
    public:
        
        Vector3D position;

        //basis vectors,

        // 1,0,0
        Vector3D right;
        Vector3D up;
        //0,0,1
        Vector3D forward;

        bool isPlayer=false;
        
        
        Vector3D OrientationVector = Vector3D(1.0f,0.0f,1.0f);

        
        TransformComponent(Vector3D pos, bool shouldDrawBasis,const FigureComponent *figure);
                
        
        ~TransformComponent();


        void init() override;

        void update(float deltaTime) override;

        void draw(Shader &shader) override;

        void Traslation(Vector3D move);

        void Scale(Vector3D scale);

        void RotationX(float angle);

        void RotationY(float angle);

        void RotationZ(float angle);

        void RotationAboutAxis(Vector3D n,float angle);

        void ShouldDrawBasis(bool isDraw){
            mDrawBasis = isDraw;
        }        

        FigureComponent* getMainFigureComponent() const{
            return mainFigureComponent;
        }      
    
        void OnCollisionEnter(TransformComponent *en1, TransformComponent *en2, float depth, Vector3D normalCollision);
    
    
    private:

        //for now get refernece to cube but we can abstract the figures more
        FigureComponent *mainFigureComponent;
        RayFigure *forwardFigure=nullptr;
                
        bool mCube= false;
        bool mTriangle= false;
        bool mPlane = false;
        bool mDrawBasis = false;

};  