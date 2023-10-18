#pragma once
#include "Components.h"

#include "ShaderClass.h"

class FigureComponent;

class TrianguleFigure: public FigureComponent{

    public:
        
        TrianguleFigure(Shader& shader, Vector3D scale, const char* image);
        ~TrianguleFigure();

        void init() override;
        
        void applyTransforms() override;
        
        void drawObject() override;



    private:
        void drawTriangle();


};