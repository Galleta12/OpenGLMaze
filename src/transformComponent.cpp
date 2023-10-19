#include "TransformComponent.h"
#include "TrianguleFigure.h"
#include "CubeFigure.h"
#include "RayFigure.h"
#include "PlaneFigure.h"
#include <typeinfo>

TransformComponent::TransformComponent(Vector3D pos, bool shouldDrawBasis, const FigureComponent *figure)
{

    std::string figureType = typeid(*figure).name();
    
    if (figureType == typeid(TrianguleFigure).name()) {
        
        mTriangle = true;
    }
    else if(figureType == typeid(CubeFigure).name()){
        mCube = true;
    }
    else if(figureType == typeid(PlaneFigure).name()){
        mPlane = true;
    }

    mDrawBasis = shouldDrawBasis;
    position = pos;


}



TransformComponent::~TransformComponent()
{
}

void TransformComponent::init()
{

    if(mTriangle){
        mainFigureComponent = &entity->getComponent<TrianguleFigure>();
    }
    else if(mCube){
        mainFigureComponent = &entity->getComponent<CubeFigure>();

    }
    else if(mPlane){
        mainFigureComponent = &entity->getComponent<PlaneFigure>();

    }


}

void TransformComponent::update(float deltaTime)
{
    //we always traslate to the current position
    Traslation(position);

}

void TransformComponent::draw(Shader &shader)
{
}

void TransformComponent::Traslation(Vector3D move)
{
    position = move;
    mainFigureComponent->TraslateFigure(move);

}

void TransformComponent::Scale(Vector3D scale)
{

    mainFigureComponent->ScaleFigure(scale);  

}

void TransformComponent::RotationX(float angle)
{
    mainFigureComponent->RotateXFigure(angle);
}

void TransformComponent::RotationY(float angle)
{
    mainFigureComponent->RotateYFigure(angle);
}

void TransformComponent::RotationZ(float angle)
{
    mainFigureComponent->RotateZFigure(angle);
}

void TransformComponent::RotationAboutAxis(Vector3D n, float angle)
{
    
    mainFigureComponent->RotationAboutAxisFigure(n,angle);

}

void TransformComponent::OnCollisionEnter(TransformComponent *en1, TransformComponent *en2, float depth, Vector3D normalCollision)
{

    if(en1->isPlayer == false) return;

    // std::cout << "normal" << normalCollision << std::endl;
    // std::cout << "depth" << depth << std::endl;

    Vector3D newPos = normalCollision * depth;
    

    //std::cout << "depth" << newPos << std::endl;

    // en1->position += newPos;

    position += newPos;

}

