#pragma once
#include "Components.h"

#include "ShaderClass.h"
#include "Vector3D.h"
class FigureComponent;

class RayFigure : public FigureComponent{
 
        public:
            RayFigure(Shader& shader, Vector3D scale,Texture &tex, Vector3D orientation);
            ~RayFigure();

            void init() override;
            
            void applyTransforms() override;
            
            void drawObject() override;


        private:
            void drawRay();

};

