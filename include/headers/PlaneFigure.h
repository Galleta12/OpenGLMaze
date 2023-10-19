#pragma once
#include "Components.h"

#include "ShaderClass.h"

class FigureComponent;
class PlaneFigure : public FigureComponent{

        
        public:
            PlaneFigure(Shader& shader, Vector3D scale,Texture &tex);
            ~PlaneFigure();

            void init() override;
            
            void applyTransforms() override;
            
            void drawObject() override;

            void draw(Shader &shader) override;

        private:
            void drawPlane();
           

};
