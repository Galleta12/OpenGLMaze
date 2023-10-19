#include "FigureComponent.h"

//for now figures
// Vertices coordinates


 
FigureComponent::FigureComponent(float red, float green, float blue, Shader &shader, Vector3D scale)
{

}

FigureComponent::FigureComponent(Shader &shader, Vector3D scale, Texture &tex)
{
    //at the start eh modelmatrix is the identity
    mModelMatrix->loadIdentity();
    scaleFactorFigure = scale;
    texture = &tex;

}


void FigureComponent::update(float deltaTime)
{

    //this should be a copy this means that all the changes done
    //should not affect the modelMatrix. only affect the copyMatrix
    copyMatrix = mModelMatrix->getModelMatrix();
    //load identity?
    //copyMatrix.loadIdentity();

}

void FigureComponent::draw(Shader &shader)
{
    if(!isDraw)return;

    //shader.use();
    // Binds texture so that is appears in rendering
    texture->Bind();
    
    //if there is specular tex we bind it
    // if(specularTex  != nullptr){
    //     specularTex->Bind();
    // }
	// Bind the VAO so OpenGL knows to use it
	VAO1->Bind();
    
    mModelMatrix->loadIdentity();
    mModelMatrix->pushMatrix();
    
    //the draws are handle each object
    applyTransforms();
   
    //mModelMatrix->traslation(Vector3D(2.0f,2.0f,0.0f));

    shader.set_model_matrix(mModelMatrix->getMatrix());
    
    //draw object
    //this is handle by each object individually
    drawObject();
    
	//glDrawElements(GL_TRIANGLES, sizeof(indicesArray) / sizeof(int), GL_UNSIGNED_INT, 0);
    
    mModelMatrix->popMatrix();

}
//set up vao for vertex array
//buffer array and indices.
void FigureComponent::setVerticesBuffer(Shader& shader,GLfloat *verticesArray ,  GLuint *indicesArray)
{
    
    //populate an array using the pointer

    
    
    //active the shader
    //shader.Activate();    
    // Generates Vertex Array Object and binds it
    VAO1 = std::make_unique<VAO>();
    VAO1->Bind();
    // Generates Vertex Buffer Object and links it to vertices
 

    VBO1 = std::make_unique<VBO>(verticesArray, verticesArraySize);
    // Generates Element Buffer Object and links it to indices
    EBO1 = std::make_unique<EBO>(indicesArray, indicesArraySize);
    // Links VBO attributes such as coordinates and colors to VAO
	VAO1->LinkAttrib(*VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO1->LinkAttrib(*VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1->LinkAttrib(*VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1->LinkAttrib(*VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1->Unbind();
	VBO1->Unbind();
	EBO1->Unbind();

}
void FigureComponent::setUpTextureAndModelMatrx(Shader &shader)
{
   
    
    
    mModelMatrix->loadIdentity();
    mModelMatrix->traslation(Vector3D(0.0f, 0.0f, 0.0f));
    
    //set up the model matrix in the shader;
    shader.set_model_matrix(mModelMatrix->getMatrix());

    //texture = std::make_unique<Texture>(image, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    
    //texture->texUnit(shader, "tex0", 0);

}


void FigureComponent::applyTransforms()
{
    mModelMatrix->transformationMatrix(copyMatrix.getMatrix());
}






void FigureComponent::setColor(float red, float green, float blue)
{
    mRed = red;
    mGreen = green;
    mBlue = blue;
}

void FigureComponent::TraslateFigure(Vector3D move)
{
    copyMatrix.traslation(move);
}

void FigureComponent::ScaleFigure(Vector3D scale)
{
    scaleFactorFigure = scale;
    copyMatrix.scale(scale);
}

void FigureComponent::RotateXFigure(float angle)
{
    copyMatrix.rotationX(angle);
}

void FigureComponent::RotateYFigure(float angle)
{
    copyMatrix.rotationY(angle);
}

void FigureComponent::RotateZFigure(float angle)
{
    copyMatrix.rotationZ(angle);
}

void FigureComponent::RotationAboutAxisFigure(Vector3D n, float angle)
{
    copyMatrix.rotationAboutAnAxis(n, angle);
}
