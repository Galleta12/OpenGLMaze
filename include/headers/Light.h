#pragma once
#include <ECS.h>
#include "Components.h"

#include "ShaderClass.h"


class LightSource : public Entity{

        
        public:
            
            LightSource(Manager& mManager,Shader& shader,Vector3D position ,Vector3D color,float a, int lighNum);
            
            ~LightSource(){
                lightVAO->Delete();
                lightVBO->Delete();
                lightEBO->Delete();
            }

            void update(float deltaTime) override;
                
            void draw(Shader &shader) override;

            const Vector3D &getPosition(){
                return mPosition;
            };
            
            const Vector3D &getColor(){
                return mColor;
            };
            const float &getLastColorA(){
                return rgba;
            };

            const int numofLight;

        private:
            
            float rgba = 0.0f;
            std::unique_ptr<ModelMatrix>  mModelMatrix = std::make_unique<ModelMatrix>();
            Vector3D mColor;
            Vector3D mPosition;
            
            Shader& lightShader;
            
            VAO *lightVAO = nullptr;

            VBO *lightVBO = nullptr;

            EBO *lightEBO = nullptr;

            float tempAngle = 0.0f;
            void setUpArrayBuffer();

};