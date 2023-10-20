#include "PlaneFigure.h"

PlaneFigure::PlaneFigure(Shader &shader, Vector3D scale, Texture &tex)
:FigureComponent(shader,scale,tex)
{

    // Vertices coordinates
    GLfloat verticesPlane[] =
    { //     COORDINATES     /        COLORS        /    TexCoord    /       NORMALS     //
	-1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	-1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f
    };

    // Indices for vertices order
    GLuint indicesPlane[] =
    {
        0, 1, 2,
        0, 2, 3
    };
    specularTex = new Texture("planksSpec.png", GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE);
    
    specularTex->texUnit(shader, "tex1", 1);



    verticesArraySize = sizeof(verticesPlane);
    indicesArraySize = sizeof(indicesPlane);
    
    setVerticesBuffer(shader,verticesPlane, indicesPlane);
    
    setUpTextureAndModelMatrx(shader);

}

PlaneFigure::~PlaneFigure()
{
}

void PlaneFigure::init()
{
}

void PlaneFigure::applyTransforms()
{
    FigureComponent::applyTransforms();   
}

void PlaneFigure::drawObject()
{
    drawPlane();
}

void PlaneFigure::draw(Shader &shader)
{
    //for specular calculations
    specularTex->Bind();
    //shininess
    shader.set_material_shininess(16.0f);
    FigureComponent::draw(shader);

}

void PlaneFigure::drawPlane()
{
  	glDrawElements(GL_TRIANGLES,  indicesArraySize / sizeof(int), GL_UNSIGNED_INT, 0);

}
