#include "Matrices.h"
#include <cmath>
#include <vector>
#include <iostream>
//remember that on the shader we are using row major

ModelMatrix::ModelMatrix()
{

    loadIdentity();

}

ModelMatrix::~ModelMatrix()
{
}

void ModelMatrix::loadIdentity()
{
    matrix = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

}

std::vector<float> ModelMatrix::copyMatrix() const
{
    std::vector<float> newMatrix(16, 0.0f);
    for (int i = 0; i < 16; ++i) {
        newMatrix[i] = matrix[i];
    }
    return newMatrix;
}


void ModelMatrix::addTransformation(const std::vector<float>& matrix2)
{
    int counter = 0;
    std::vector<float> newMatrix(16, 0.0f);
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            for (int i = 0; i < 4; ++i) {
                newMatrix[counter] += matrix[row * 4 + i] * matrix2[col + 4 * i];
            }
            counter++;
        }
    }
    matrix = newMatrix;

}

void ModelMatrix::addNothing()
{

    std::vector<float> otherMatrix = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    addTransformation(otherMatrix);

}

void ModelMatrix::pushMatrix()
{

    matrixStack.push_back(copyMatrix());
}

void ModelMatrix::popMatrix()
{
    if (!matrixStack.empty()) {
        matrix = matrixStack.back();
        matrixStack.pop_back();
    }
}

std::vector<float> ModelMatrix::getMatrix()
{
    return matrix;
}

ModelMatrix ModelMatrix::getModelMatrix()
{
    
    
    return *this;
}

void ModelMatrix::transformationMatrix(const std::vector<float> &matrix2)
{
    addTransformation(matrix2);

}

void ModelMatrix::traslation(Vector3D move)
{
    
    //homogeneus system
    std::vector<float> otherMatrix = {
        1.0f,   0.0f,   0.0f,  move.x,
        0.0f,   1.0f,   0.0f,  move.y,
        0.0f,   0.0f,   1.0f,  move.z,
        0.0f,   0.0f,   0.0f,  1.0f  
    };
    addTransformation(otherMatrix);

}

void ModelMatrix::scale(Vector3D scale)
{

    std::vector<float> otherMatrix = {
        scale.x, 0.0f,   0.0f,   0.0f,
        0.0f,   scale.y, 0.0f,   0.0f,
        0.0f,   0.0f,   scale.z, 0.0f,
        0.0f,   0.0f,   0.0f,    1.0f  
    };
    addTransformation(otherMatrix);

}


//  #for rotations more complex
//  # an angle and 3 values that represent the vector to rotate about
//  #angle in randians


void ModelMatrix::rotationX(float angle)
{
    float C = std::cos(angle);
    float S = std::sin(angle);
    std::vector<float> otherMatrix = {
        1.0f,   0.0f,   0.0f,  0.0f,
        0.0f,   C,      -S,    0.0f,
        0.0f,   S,       C,    0.0f,
        0.0f,   0.0f,   0.0f,  1.0f  
    };
    addTransformation(otherMatrix);

}




//y rot
//  other_matrix =        [c, 0, s, 0,
//                         0, 1, 0, 0,
//                         -s, 0, c, 0,
//                         0, 0, 0, 1]
void ModelMatrix::rotationY(float angle)
{
    float C = std::cos(angle);
    float S = std::sin(angle);
    std::vector<float> otherMatrix = {
        C,      0.0f,     S,   0.0f,
        0.0f,   1.0f,   0.0f,  0.0f,
        -S,     0.0f,    C,    0.0f,
        0.0f,   0.0f,   0.0f,  1.0f  
    };
    addTransformation(otherMatrix);
}


//  other_matrix =        [c, -s, 0, 0,
//                         s, c, 0, 0,
//                         0, 0, 1, 0,
//                         0, 0, 0, 1]

void ModelMatrix::rotationZ(float angle)
{
    float C = std::cos(angle);
    float S = std::sin(angle);
    std::vector<float> otherMatrix = {
        C,       -S,      0.0f,  0.0f,
        S,        C,      0.0f,  0.0f,
        0.0f,     0.0f,   1.0f,  0.0f,
        0.0f,     0.0f,   0.0f,  1.0f  
    };
    addTransformation(otherMatrix);
}

void ModelMatrix::rotationAboutAnAxis(Vector3D n, float angle)
{

    // Normalize the axis vector to ensure it's a unit vector
    Vector3D axis= n.normalize();

    float c = std::cos(angle);
    float s = std::sin(angle);
    
    float t = 1.0f - c;
    float x = axis.x;
    float y = axis.y;
    float z = axis.z;

    // Create the rotation matrix using the Rodrigues' formula
    std::vector<float> otherMatrix = {
        t * x * x + c,     t * x * y - s * z,  t * x * z + s * y, 0.0f,
        t * x * y + s * z, t * y * y + c,     t * y * z - s * x, 0.0f,
        t * x * z - s * y, t * y * z + s * x, t * z * z + c,     0.0f,
        0.0f,              0.0f,              0.0f,              1.0f
    };

    addTransformation(otherMatrix);

}

std::string ModelMatrix::ToStringPrinter()
{

    // Implement the __str__ function to return a string representation
    // of the matrix. You can format it as you like.
    std::string ret_str = "";
    int counter = 0;
    for (int i = 0; i < 4; ++i) {
        ret_str += "[";
        for (int j = 0; j < 4; ++j) {
            ret_str += " " + std::to_string(matrix[counter]) + " ";
            counter++;
        }
        ret_str += "]\n";
    }
    return ret_str;

}





ViewMatrix::ViewMatrix()
{
    eye = Point(0.0f,0.0f,0.0f);
    u = Vector3D(1.0f,0.0f,0.0f);
    v = Vector3D(0.0f,1.0f,0.0f);
    n = Vector3D(0.0f,0.0f,1.0f);
}

ViewMatrix::~ViewMatrix()
{


}



//first get the point were we want to look
//eye is the point of origin of the camera
//ceneter where we want to look
//up an arbitrary y axis
void ViewMatrix::look(Point _eye, Vector3D center, Vector3D up)
{
    eye = Point(_eye.x,_eye.y,_eye.z);
    //this should be backwards eye - center, vector towards us,
    //eye is a point so for this calculation we conver it to a vector since my  code doesnt allow point and vetor calculations
    Vector3D tempEye(eye.x, eye.y, eye.z);
    Vector3D nn = tempEye - center; 
    
    n = nn.normalize();
    
    //cordinate frame perpendicular cross products
    Vector3D uu = Vector3D::Cross(up,n);
    u = uu.normalize();

    v = Vector3D::Cross(n,u);


}

//how far we want to move relative to the camera coordinate frames
void ViewMatrix::slide(float delU, float delV, float delN)
{
    //u =x
    //v =ys
    //n =z
    eye.x += u.x * delU + v.x * delV + n.x * delN;
    eye.y += u.y * delU + v.y * delV + n.y * delN;
    eye.z += u.z * delU + v.z * delV + n.z * delN;
}
//rotation about a n axis
//find new values for u and v. x and y. n unchanged.
//n=z
//u=x
//v=y


void ViewMatrix::roll(float angle)
{
    float C = std::cos(angle);
    float S = std::sin(angle);

    Vector3D tmpU = u * C + v * S;
    v = u * -S + v * C;
    u = tmpU;
}
//rotation about the v=y
void ViewMatrix::yaw(float angle)
{
    float C = std::cos(angle);
    float S = std::sin(angle);
    
    Vector3D tmpU = u * C + n * S;
    n = n * C - u * S;
    u = tmpU;
}
//rotation about the u=x
void ViewMatrix::pitch(float angle)
{
    float C = std::cos(angle);
    float S = std::sin(angle);

    Vector3D tmpV = v * C + n * S;
    n = n * C - v * S;
    v = tmpV;
}
//this is not working for now
void ViewMatrix::walkYAxis(float delX, float delY)
{
    // Move along the direction of n  and x (z-axis), but only in the xz plane
    
    
    eye.x += delX;
    eye.z += delY;
}

void ViewMatrix::walkFlat(float delX, float delz)
{

    //u =x
    //v =ys
    //n =z
    eye.x += u.x * delX  + n.x * delz;
    eye.z += u.z * delX + n.z * delz;


}

void ViewMatrix::TurnFirstCamView(float turn)
{
    // Rotate around the up vector (Y-axis), preserving the up vector (v)
    float cosA = std::cos(turn);
    float sinA = std::sin(turn);

    Vector3D tempU = u * cosA + n * sinA;
    n =  n * cosA - u * sinA  ;
    u = tempU;
}

void ViewMatrix::PitchFirstCamView(float angle)
{


}

std::vector<float> ViewMatrix::getMatrix()
{
    
    Vector3D minusEye = Vector3D(-eye.x, -eye.y, -eye.z);
    matrix = {
        u.x, u.y, u.z, Vector3D::Dot(minusEye,u), 
        v.x, v.y, v.z, Vector3D::Dot(minusEye,v), 
        n.x, n.y, n.z, Vector3D::Dot(minusEye,n),
        0,   0,   0,       1, 
         
    };
    
    return matrix;

}

ProjectionMatrix::ProjectionMatrix()
{

    left = -1.0f;
    right = 1.0f;
    bottom = -1.0f;
    top = 1.0f;
    nearPlane = -1.0f;
    farPlane = -1.0f;

    isOrthographic = true;

}



ProjectionMatrix::~ProjectionMatrix()
{

}

void ProjectionMatrix::setOrthographic(float _left, float _right, float _bottom, float _top, float _nearPlane, float _farPlane)
{
        
    left = _left;
    right =_right;
    bottom = _bottom;
    top =_top;
    nearPlane = _nearPlane;
    farPlane = _farPlane;

    isOrthographic = true;

}

//filed of view in y
//aspect ration
void ProjectionMatrix::setPerspective(float fov, float aspect, float _nearPlane, float _farPlane)
{
    nearPlane = _nearPlane;
    
    farPlane = _farPlane;
    
    top =_nearPlane * std::tan(fov/2);
    
    bottom = -top;

    //width and height
    right = top * aspect;
    left = -right;
    isOrthographic = false;


}

std::vector<float> ProjectionMatrix::getMatrix()
{
    
    
    if (isOrthographic){
        float A = 2.0f / (right - left);
        float B = -(right + left) / (right - left);
        float C = 2.0f / (top - bottom);
        float D = -(top + bottom) / (top - bottom);
        float E = 2.0f / (nearPlane - farPlane);
        float F = (nearPlane + farPlane) / (nearPlane - farPlane);

        
        //Homeguenouse, when is one it is a point
        matrix = {
            A, 0.0f, 0.0f, B,
            0.0f, C, 0.0f, D,
            0.0f, 0.0f, E, F,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        return matrix;
    }
    else{
        // Set up a matrix for a Perspective projection
        // Remember that it's a non-linear transformation, so the bottom row is different
        //homogeneous division for the depth
        float A = (2.0f * nearPlane) / (right - left);
        //traslation factor
        float B = (right + left) / (right - left);
        //c scaling factor of y
        float C = (2.0f * nearPlane) / (top - bottom);
        
        float D = (top + bottom) / (top - bottom);

        float E = -(farPlane + nearPlane) / (farPlane - nearPlane);
        
        float F = -(2.0f * farPlane * nearPlane) / (farPlane - nearPlane);

        matrix = {
            A,    0.0f,  B,   0.0f,
            0.0f, C,     D,   0.0f,
            0.0f, 0.0f,  E,    F,
            0.0f, 0.0f, -1.0f, 0.0f
        };
    
        return matrix;
    }        
    
   
    
}


//just for testing purposes

ProjectionViewMatrix::ProjectionViewMatrix()
{

}

ProjectionViewMatrix::~ProjectionViewMatrix(){}


std::vector<float> ProjectionViewMatrix::getMatrix(){

    matrix = {
         0.45052942369783683, 0.0f, -0.15017647456594563, 0.0f,
        -0.10435451285616304f, 0.5217725642808152f, -0.3130635385684891f, 0.0f,
        -0.2953940042189954f, -0.5907880084379908f, -0.8861820126569863f, 3.082884480118567f,
        -0.2672612419124244f, -0.5345224838248488f, -0.8017837257372732f, 3.7416573867739413f
    };

    return matrix;

}
