#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <string>

#include<glad/glad.h>
#include<GLFW/glfw3.h>



#include "Vector3D.h"
#include "Point.h"


//4x4 matrix
class ModelMatrix{
    public:
        
        ModelMatrix();
        ~ModelMatrix();
        
        void loadIdentity();
        std::vector<float> copyMatrix() const;
        //matrix multiplication
        void addNothing();
        // for the stack
        void pushMatrix();
        void popMatrix();

        //matrix transformations

        void traslation(Vector3D move);
        void scale(Vector3D scale);
        
        void rotationX(float angle);
        void rotationY(float angle);
        void rotationZ(float angle);
        
        void rotationAboutAnAxis(Vector3D n,float angle);


        
        void transformationMatrix(const std::vector<float>& matrix2);

        std::vector<float> getMatrix();
        
        ModelMatrix getModelMatrix();
        
     

        std::string ToStringPrinter();

        
    private:
        void addTransformation(const std::vector<float>& matrix2);
        std::vector<float> matrix;
        std::vector<std::vector<float>> matrixStack;


};







class ViewMatrix{

    public:
        ViewMatrix();
        ~ViewMatrix();

        std::vector<float> getMatrix();


        void look(Point _eye, Vector3D center, Vector3D up);

        void slide(float delU, float delV, float delN);

        void roll(float angle);

        void yaw(float angle);

        void pitch(float angle);

        void walkYAxis(float delX, float delY);

        void walkFlat(float delX, float delz);
        
        void TurnFirstCamView(float turn);

        void PitchFirstCamView(float angle);
       
        Vector3D getVectorEye(){
            return Vector3D(eye.x,eye.y,eye.z);
        }


        Vector3D setEyePos(Vector3D pos){
            eye = Point(pos.x, pos.y, pos.z);
            return getVectorEye();
        }

        Vector3D getViewX(){
            return u;
        }

        Vector3D getViewY(){
            return v;
        }

        Vector3D getViewZ(){
            return n;
        }

        //get a vector eye

    private:
       
        Point eye;
        Vector3D u;
        Vector3D v;
        Vector3D n;
        
        std::vector<float> matrix;
};




class ProjectionMatrix{
    public:
        
        ProjectionMatrix();
        ~ProjectionMatrix();
        
        void setOrthographic(float _left, float _right, float _bottom, float _top, float _nearPlane, float _farPlane);
        void setPerspective(float fov, float aspect, float _nearPlane, float _farPlane);

        std::vector<float> getMatrix();
    
    private:
        
        
        float left = -1.0f;
        float right = 1.0f;
        float bottom = -1.0f;
        float top = 1.0f;
        float nearPlane = -1.0f;
        float farPlane = -1.0f;
        
        std::vector<float> matrix;
        
        bool isOrthographic;
};


class ProjectionViewMatrix{

    public:
        ProjectionViewMatrix();
        ~ProjectionViewMatrix();

        std::vector<float> getMatrix();

    private:
        std::vector<float> matrix;


};