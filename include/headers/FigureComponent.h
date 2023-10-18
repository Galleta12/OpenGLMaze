#pragma once

#include <vector>
#include <iostream>
#include <memory>

#include "Components.h"
#include "Matrices.h"
#include "Vector3D.h"
#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"


class  FigureComponent : public Component{
    
    public:
        
        bool isCube = false;
        bool isLine = false;
        bool isSphere = false;
        
        bool  isDraw = true;
        
        FigureComponent(float red, float green, float blue, Shader& shader, Vector3D scale);
        FigureComponent(Shader& shader, Vector3D scale);
        virtual ~FigureComponent(){
            VAO1->Delete();
            VBO1->Delete();
            EBO1->Delete();
            texture->Delete();
        }
        
        void update(float deltaTime) override;
        
        void draw(Shader& shader)override;
      
        void setVerticesBuffer(Shader& shader,GLfloat *verticesArray ,  GLuint *indicesArray);
        void setUpTextureAndModelMatrx(Shader& shader, const char* image);
        
        //each figure handle their onw draw object
        virtual void drawObject(){}
        virtual void applyTransforms();
        
        //function that all figures can use      
        void setColor(float red, float green, float blue);

        void TraslateFigure(Vector3D move);
        void ScaleFigure(Vector3D scale);
        void RotateXFigure(float angle);
        void RotateYFigure(float angle);
        void RotateZFigure(float angle);
        void RotationAboutAxisFigure(Vector3D n, float angle);
        
        int verticesArraySize;
        int indicesArraySize;
        //by default 1,1,1
        Vector3D scaleFactorFigure;

    
    private:
        
        float mRed, mGreen,  mBlue = 0.0f;
        //we perform here all matrix transformation to the copy.
        //later on we can apply all the transformation to the modelMatrix of the transform object
        ModelMatrix copyMatrix;
        std::unique_ptr<ModelMatrix>  mModelMatrix = std::make_unique<ModelMatrix>();

        //this can start by defaul without any constructo;
        std::unique_ptr<VAO> VAO1;

        std::unique_ptr<VBO>VBO1;     
        
        std::unique_ptr<EBO>EBO1;

        std::unique_ptr<Texture> texture;

       

};