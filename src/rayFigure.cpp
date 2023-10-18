#include "RayFigure.h"

RayFigure::RayFigure(Shader &shader, Vector3D scale, Texture &tex , Vector3D orientation)
:FigureComponent(shader,scale,tex)
{

    float scaleX = orientation.x;
    float scaleY = orientation.y;
    float scaleZ = orientation.z;
   GLfloat verticesOrientedCube[] = {
    // Front Face
    -0.5f * scaleX, -0.5f * scaleY, 0.5f * scaleZ,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.5f * scaleX, -0.5f * scaleY, 0.5f * scaleZ,   0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.5f * scaleX, 0.5f * scaleY, 0.5f * scaleZ,    0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    -0.5f * scaleX, 0.5f * scaleY, 0.5f * scaleZ,    1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

    // Back Face
    -0.5f * scaleX, -0.5f * scaleY, -0.5f * scaleZ,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
    0.5f * scaleX, -0.5f * scaleY, -0.5f * scaleZ,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
    0.5f * scaleX, 0.5f * scaleY, -0.5f * scaleZ,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
    -0.5f * scaleX, 0.5f * scaleY, -0.5f * scaleZ,  1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,

    // Right Face
    0.5f * scaleX, -0.5f * scaleY, 0.5f * scaleZ, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f * scaleX, -0.5f * scaleY, -0.5f * scaleZ, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f * scaleX, 0.5f * scaleY, -0.5f * scaleZ, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    0.5f * scaleX, 0.5f * scaleY, 0.5f * scaleZ, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,

    // Left Face
    -0.5f * scaleX, -0.5f * scaleY, 0.5f * scaleZ, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
    -0.5f * scaleX, -0.5f * scaleY, -0.5f * scaleZ, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
    -0.5f * scaleX, 0.5f * scaleY, -0.5f * scaleZ, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
    -0.5f * scaleX, 0.5f * scaleY, 0.5f * scaleZ, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,

    // Top Face
    -0.5f * scaleX, 0.5f * scaleY, 0.5f * scaleZ, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.5f * scaleX, 0.5f * scaleY, 0.5f * scaleZ, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.5f * scaleX, 0.5f * scaleY, -0.5f * scaleZ, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f * scaleX, 0.5f * scaleY, -0.5f * scaleZ, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

    // Bottom Face
    -0.5f * scaleX, -0.5f * scaleY, 0.5f * scaleZ, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
    0.5f * scaleX, -0.5f * scaleY, 0.5f * scaleZ, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
    0.5f * scaleX, -0.5f * scaleY, -0.5f * scaleZ, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
    -0.5f * scaleX, -0.5f * scaleY, -0.5f * scaleZ, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f
};


    GLuint indicesStretchedCube[] = {
        // Front Face
        0, 1, 2,
        2, 3, 0,

        // Back Face
        4, 5, 6,
        6, 7, 4,

        // Right Face
        8, 9, 10,
        10, 11, 8,

        // Left Face
        12, 13, 14,
        14, 15, 12,

        // Top Face
        16, 17, 18,
        18, 19, 16,

        // Bottom Face
        20, 21, 22,
        22, 23, 20
    };


    verticesArraySize = sizeof(verticesOrientedCube);
    indicesArraySize = sizeof(indicesStretchedCube);
    
    setVerticesBuffer(shader,verticesOrientedCube, indicesStretchedCube);
    
    setUpTextureAndModelMatrx(shader);


}

RayFigure::~RayFigure()
{
}

void RayFigure::init()
{
}

void RayFigure::applyTransforms()
{
    FigureComponent::applyTransforms();
}

void RayFigure::drawObject()
{
    drawRay();
}

void RayFigure::drawRay()
{
  	glDrawElements(GL_TRIANGLES,  indicesArraySize / sizeof(int), GL_UNSIGNED_INT, 0);

}
