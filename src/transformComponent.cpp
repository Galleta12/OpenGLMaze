#include "TransformComponent.h"
#include "TrianguleFigure.h"
#include "CubeFigure.h"
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

}

void TransformComponent::update(float deltaTime)
{



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

void TransformComponent::OnCollisionEnter(Entity *en1, Entity *en2, float depth, Vector3D normalCollision)
{


}
