#include "CameraComponent.h"



CameraComponent::CameraComponent(Vector3D _eyePosition)
{
    eyePosition = _eyePosition;
}


CameraComponent::~CameraComponent()
{
}

void CameraComponent::setLooKViewCamera(Vector3D eye, Vector3D center, Vector3D up)
{

    eyePosition = eye;
    
    Point eyeP(eye.x, eye.y, eye.z);
 
    mViewMatrix->look(eyeP, center, up);

}

void CameraComponent::setPerspectiveProjection(float fov, float _aspect, float _near, float _far)
{
    zoom = fov;
    
    mProjectionMatrix->setPerspective(zoom, _aspect, _near, _far);

}

void CameraComponent::setOrthoGraphicProjection(float _left, float _right, float _bottom, float _top, float _nearPlane, float _farPlane)
{
    mProjectionMatrix->setOrthographic(_left, _right, _bottom, _top,_nearPlane, _farPlane);
}


void CameraComponent::draw(Shader& shader)
{
    
    
    //we dont want to draw
    if(!shouldDraw)return;

    setViewShader(shader);
    setProjectionShader(shader);


}

void CameraComponent::update(float deltaTime)
{

    if(!shouldDraw)return;
    eyePosition = mViewMatrix->getVectorEye();
}

void CameraComponent::setViewShader(Shader &shader)
{
    shader.set_view_matrix(mViewMatrix->getMatrix());
}


void CameraComponent::setProjectionShader(Shader &shader)
{

    shader.set_projection_matrix(mProjectionMatrix->getMatrix());
               

}

