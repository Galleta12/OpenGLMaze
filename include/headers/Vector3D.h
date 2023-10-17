#pragma once
#include <iostream>
#include <cmath>

class Vector3D{
    public:
        float x,y,z;

        
        Vector3D();
        Vector3D(float x, float y, float z);

        ~Vector3D();
        
        
        
        //multiplicatios additions      
        Vector3D Add(const Vector3D& vec) const;
        
        Vector3D Substract(const Vector3D& vec) const;
        
        Vector3D Multiply(const Vector3D& vec)const;
        
        Vector3D Divide(const Vector3D& vec) const;
        
        
        Vector3D &operator=(const Vector3D& vec);
        //operator overload
        Vector3D operator+(const Vector3D& v1)const;
        
        Vector3D operator-(const Vector3D& v1)const;
        
        Vector3D operator*(const Vector3D& v1)const;
        
        Vector3D operator/(const Vector3D& v1)const;
        
        
        //we want the same but for accumulations operators
        Vector3D& operator+=(const Vector3D& vec);
        Vector3D& operator-=(const Vector3D& vec);
        Vector3D& operator*=(const Vector3D& vec);
        Vector3D& operator/=(const Vector3D& vec);

        //scalar multiplications
        Vector3D operator*(const float& i);
        Vector3D operator/(const float& i);
        

        Vector3D Zero();

        Vector3D normalize() const;
        
        float magnitude() const; 
        
        
        static float AngleInDeg(const Vector3D &v1, const Vector3D &v2);
        static float AngleInRad(const Vector3D &v1, const Vector3D &v2);
        
        
        static float Dot(const Vector3D& v1, const Vector3D& v2);
        
        
        static Vector3D Cross(const Vector3D& v1, const Vector3D& v2);
        
        static Vector3D RotateVectorX(const Vector3D& vec, const float& angle);
        static Vector3D RotateVectorY(const Vector3D& vec, const float& angle);
        static Vector3D RotateVectorZ(const Vector3D& vec,const float& angle);
        
        static Vector3D RotateVectorAboutAxis(const Vector3D& vec,const Vector3D& axis, const float& angle);
        
        static Vector3D Rotation(const Vector3D &vec, const Vector3D &axis, const float angle);

        static Vector3D UP();
        static Vector3D RIGHT();
        static Vector3D FORWARD();

        
        static float DistanceVec(const Vector3D& v1, const Vector3D& v2);

        //clean way to print the vectors
        
        friend std::ostream& operator <<(std::ostream& stream, const Vector3D& vec);


    private:

};