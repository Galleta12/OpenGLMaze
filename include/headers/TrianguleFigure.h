#pragma once
#include "Components.h"

#include "ShaderClass.h"

class FigureComponent;

class TrianguleFigure: public FigureComponent{

    public:
        
        TrianguleFigure(Shader& shader, Vector3D scale,Texture &tex);
        ~TrianguleFigure();

        void init() override;
        
        void applyTransforms() override;
        
        void drawObject() override;

        void draw(Shader &shader) override;


    private:
        void drawTriangle();


};