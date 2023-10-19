#pragma once
#include <ECS.h>
#include "Components.h"

#include "ShaderClass.h"


class LightSource : public Entity{

        
        public:
            
            LightSource(Manager& mManager,Shader& shader,Vector3D position ,Vector3D color,float a);
            
            ~LightSource(){
                lightVAO->Delete();
                lightVBO->Delete();
                lightEBO->Delete();
            }

            void update(float deltaTime) override;
                
            void draw(Shader &shader) override;


            void setUpArrayBuffer();
        private:
            
            float rgba = 0.0f;
            std::unique_ptr<ModelMatrix>  mModelMatrix = std::make_unique<ModelMatrix>();
            Vector3D mColor;
            Vector3D mPosition;
            
            Shader& lightShader;
            
            VAO *lightVAO = nullptr;

            VBO *lightVBO = nullptr;

            EBO *lightEBO = nullptr;


};