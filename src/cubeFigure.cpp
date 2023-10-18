#include "CubeFigure.h"


CubeFigure::CubeFigure(Shader& shader, Vector3D scale,Texture &tex)
:FigureComponent(shader,scale,tex)
{
    GLfloat verticesCube[] = {
      // Position                // Colors                // Texture Coordinates    // Normals
// Front Face
-0.5f, -0.5f,  0.5f,       1.0f, 0.0f, 0.0f,      0.0f, 0.0f,           0.0f, 0.0f, 1.0f,
0.5f, -0.5f,  0.5f,       0.0f, 1.0f, 0.0f,      1.0f, 0.0f,           0.0f, 0.0f, 1.0f,
0.5f,  0.5f,  0.5f,       0.0f, 0.0f, 1.0f,      1.0f, 1.0f,            0.0f, 0.0f, 1.0f,
-0.5f,  0.5f,  0.5f,       1.0f, 1.0f, 0.0f,      0.0f, 1.0f,            0.0f, 0.0f, 1.0f,

// Back Face
-0.5f, -0.5f, -0.5f,       1.0f, 0.0f, 0.0f,      1.0f, 0.0f,            0.0f, 0.0f, -1.0f,
0.5f, -0.5f, -0.5f,       0.0f, 1.0f, 0.0f,      0.0f, 0.0f,             0.0f, 0.0f, -1.0f,
0.5f,  0.5f, -0.5f,       0.0f, 0.0f, 1.0f,      0.0f, 1.0f,             0.0f, 0.0f, -1.0f,
-0.5f,  0.5f, -0.5f,       1.0f, 1.0f, 0.0f,      0.0f, 1.0f,            0.0f, 0.0f, -1.0f,

// Right Face
0.5f, -0.5f,  0.5f,       1.0f, 0.0f, 0.0f,      0.0f, 0.0f,             1.0f, 0.0f, 0.0f,
0.5f, -0.5f, -0.5f,       0.0f, 1.0f, 0.0f,      1.0f, 0.0f,             1.0f, 0.0f, 0.0f,
0.5f,  0.5f, -0.5f,       0.0f, 0.0f, 1.0f,      1.0f, 1.0f,             1.0f, 0.0f, 0.0f,
0.5f,  0.5f,  0.5f,       1.0f, 1.0f, 0.0f,      0.0f, 1.0f,             1.0f, 0.0f, 0.0f,

// Left Face
-0.5f, -0.5f,  0.5f,       1.0f, 0.0f, 0.0f,      1.0f, 0.0f,             -1.0f, 0.0f, 0.0f,
-0.5f, -0.5f, -0.5f,       0.0f, 1.0f, 0.0f,      0.0f, 0.0f,             -1.0f, 0.0f, 0.0f,
-0.5f,  0.5f, -0.5f,       0.0f, 0.0f, 1.0f,      0.0f, 1.0f,             -1.0f, 0.0f, 0.0f,
-0.5f,  0.5f,  0.5f,       1.0f, 1.0f, 0.0f,      0.0f, 1.0f,             -1.0f, 0.0f, 0.0f,

// Top Face
-0.5f,  0.5f,  0.5f,       1.0f, 0.0f, 0.0f,      0.0f, 0.0f,             0.0f, 1.0f, 0.0f,
0.5f,  0.5f,  0.5f,       0.0f, 1.0f, 0.0f,      1.0f, 0.0f,             0.0f, 1.0f, 0.0f,
0.5f,  0.5f, -0.5f,       0.0f, 0.0f, 1.0f,      1.0f, 1.0f,             0.0f, 1.0f, 0.0f,
-0.5f,  0.5f, -0.5f,       1.0f, 1.0f, 0.0f,      0.0f, 1.0f,             0.0f, 1.0f, 0.0f,

// Bottom Face
-0.5f, -0.5f,  0.5f,       1.0f, 0.0f, 0.0f,       0.0f, 0.0f,            0.0f, -1.0f, 0.0f,
0.5f, -0.5f,  0.5f,       0.0f, 1.0f, 0.0f,       1.0f, 0.0f,            0.0f, -1.0f, 0.0f,
0.5f, -0.5f, -0.5f,       0.0f, 0.0f, 1.0f,       1.0f, 1.0f,            0.0f, -1.0f, 0.0f,
-0.5f, -0.5f, -0.5f,       1.0f, 1.0f, 0.0f,       0.0f, 1.0f,            0.0f, -1.0f, 0.0f
    };

    GLuint indicesCube[] = {
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
    
    
    
    verticesArraySize = sizeof(verticesCube);
    indicesArraySize = sizeof(indicesCube);
    
    setVerticesBuffer(shader,verticesCube, indicesCube);
    
    setUpTextureAndModelMatrx(shader);


}

CubeFigure::~CubeFigure()
{
}

void CubeFigure::init()
{
}

void CubeFigure::applyTransforms()
{
    FigureComponent::applyTransforms();   
}

void CubeFigure::drawObject()
{
    drawCube();
}

//draw
void CubeFigure::drawCube()
{
  	glDrawElements(GL_TRIANGLES,  indicesArraySize / sizeof(int), GL_UNSIGNED_INT, 0);


}
