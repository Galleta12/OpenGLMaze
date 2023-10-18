#pragma once
#include <vector>
#include <memory>


#include "ECS.h"
#include "Components.h"

#include "Vector3D.h"
#include "Point.h"
#include "Matrices.h"
#include "ShaderClass.h"

class FigureComponent;
class TrianguleFigure;
class CubeFigure;
class TransformComponent : public Component{
    public:
        
        Vector3D position;

        //basis vectors,

        // 1,0,0
        Vector3D right;
        Vector3D up;
        Vector3D forward;

        
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
    
        void OnCollisionEnter(Entity *en1,Entity *en2, float depth, Vector3D normalCollision);
    
    
    private:
        
        //for now get refernece to cube but we can abstract the figures more
        FigureComponent *mainFigureComponent;
        
        bool mCube= false;
        bool mTriangle= false;
        bool mDrawBasis = false;

};