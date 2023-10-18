#pragma once
#include "Components.h"

#include "ShaderClass.h"

class FigureComponent;

class CubeFigure : public FigureComponent{

        
        public:
            CubeFigure(Shader& shader, Vector3D scale, const char* image);
            ~CubeFigure();

            void init() override;
            
            void applyTransforms() override;
            
            void drawObject() override;



        private:
            void drawCube();

};