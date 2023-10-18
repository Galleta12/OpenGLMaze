#include "Vector3D.h"

#include "RadToDegree.h"




Vector3D::Vector3D():x(0.0f),y(0.0f),z(0.0f)
{
}

Vector3D::Vector3D(float x, float y, float z)
{
    this->x=x;
    this->y=y;
    this->z=z;

}

Vector3D::~Vector3D()
{

}

Vector3D Vector3D::Add(const Vector3D &vec) const
{    
    return Vector3D(x + vec.x,y + vec.y, z + vec.z);    
}


Vector3D Vector3D::Substract(const Vector3D &vec) const
{
    return Vector3D(x - vec.x, y - vec.y, z - vec.z);    
}


Vector3D Vector3D::Multiply(const Vector3D &vec) const
{
    return Vector3D(x * vec.x, y * vec.y, z * vec.z);
}



Vector3D Vector3D::Divide(const Vector3D &vec) const
{
    return Vector3D(x / vec.x, y / vec.y, z / vec.z);
}

Vector3D &Vector3D::operator=(const Vector3D &vec)
{
    x=vec.x;
    y=vec.y;
    z=vec.z;
    return *this;
}

Vector3D Vector3D::operator+(const Vector3D &v1)const
{
    return this->Add(v1);
}

Vector3D Vector3D::operator-(const Vector3D &v1)const
{
    return this->Substract(v1);
}

Vector3D Vector3D::operator*(const Vector3D &v1)const
{
    return this->Multiply(v1);
}

Vector3D Vector3D::operator/(const Vector3D &v1)const
{
    return this->Divide(v1);
}


//cummulative
Vector3D &Vector3D::operator+=(const Vector3D &vec)
{
    this->x += vec.x;
    this->y += vec.y;
    this->z += vec.z;

    return *this;
}

Vector3D &Vector3D::operator-=(const Vector3D &vec)
{
    this->x -= vec.x;
    this->y -= vec.y;
    this->z -= vec.z;

    return *this;
}

Vector3D &Vector3D::operator*=(const Vector3D &vec)
{
    this->x *= vec.x;
    this->y *= vec.y;
    this->z *= vec.z;

    return *this;
    
}

Vector3D &Vector3D::operator/=(const Vector3D &vec)
{
    this->x /= vec.x;
    this->y /= vec.y;
    this->z /= vec.z;

    return *this;
    
}



//sccalar operators
Vector3D Vector3D::operator*(const float &i)
{
    // this->x *= i;
    // this->y *= i;
    // this->z *= i;
    return Vector3D(x*i,y*i,z*i);
    //return *this;
}

Vector3D Vector3D::operator/(const float &i)
{
    // this->x /= i;
    // this->y /= i;
    // this->z /= i;

    // return *this;
    return Vector3D(x/i,y/i,z/i);
}

Vector3D Vector3D::Zero()
{
    return Vector3D(0.0f,0.0f,0.0f);
}


Vector3D Vector3D::normalize() const
{
    
    float magnitude = this->magnitude();
    
    
    Vector3D n(this->x,this->y,this->z);
    n.x /= magnitude; 
    n.y /= magnitude;
    n.z /= magnitude;
    
    return n;

}




float Vector3D::magnitude() const
{
    return std::sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
}


float Vector3D::Dot(const Vector3D &v1, const Vector3D &v2)
{  
    return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}


float Vector3D::AngleInDeg(const Vector3D &v1, const Vector3D &v2)
{
    float dotProduct = Vector3D::Dot(v1,v2);

    float magnitude1 = v1.magnitude();
    
    float magnitude2 = v2.magnitude();

    float angleRad = std::acos(dotProduct/(magnitude1 * magnitude2));
    //convert into degrees
    float angleDeg = RadToDegree::convert(angleRad);


    return angleDeg;

}

float Vector3D::AngleInRad(const Vector3D &v1, const Vector3D &v2)
{
    
    float dotProduct = Vector3D::Dot(v1,v2);

    float magnitude1 = v1.magnitude();
    
    float magnitude2 = v2.magnitude();

    float angleRad = std::acos(dotProduct/(magnitude1 * magnitude2));
 


    return  angleRad ;
}

//cross product
// i = aybz - azby
// j = azbx - axbz
// k = axby - aybx
//     return Vector(self.y*other.z - self.z*other.y, self.z*other.x - self.x*other.z, self.x*other.y - self.y*other.x)
Vector3D Vector3D::Cross(const Vector3D &v1, const Vector3D &v2)
{    
    float i= (v1.y * v2.z) - (v1.z * v2.y);
    float j= (v1.z * v2.x) - (v1.x * v2.z);   
    float k= (v1.x * v2.y) - (v1.y * v2.x);

    return Vector3D(i,j,k);
}

Vector3D Vector3D::RotateVectorX(const Vector3D& vec,const float &angle)
{
    float newX = vec.x;
    float newY = std::cos(angle) * vec.y - std::sin(angle) * vec.z;
    float newZ = std::sin(angle) * vec.y + std::cos(angle) * vec.z;
    return Vector3D(newX, newY, newZ);
}


// float C = std::cos(angle);
//     float S = std::sin(angle);
    
//     Vector3D tmpU = u * C + n * S;
//     n = n * C - u * S;
//     u = tmpU;
Vector3D Vector3D::RotateVectorY(const Vector3D& vec,const float &angle)
{
    float newX = std::cos(angle) * vec.x + std::sin(angle) * vec.z;
    float newY = vec.y;
    float newZ = -std::sin(angle) * vec.x + std::cos(angle) * vec.z;
    return Vector3D(newX, newY, newZ);
}

Vector3D Vector3D::RotateVectorZ(const Vector3D& vec,const float &angle)
{
    float newX = std::cos(angle) * vec.x - std::sin(angle) * vec.y;
    float newY = std::sin(angle) * vec.x + std::cos(angle) * vec.y;
    float newZ = vec.z;
    return Vector3D(newX, newY, newZ);
}

Vector3D Vector3D::RotateVectorAboutAxis(const Vector3D &vec, const Vector3D &axis, const float &angle)
{
    // Normalize the axis vector to ensure it's a unit vector
    Vector3D normalizedAxis = axis.normalize();

    float c = std::cos(angle);
    float s = std::sin(angle);
    float t = 1.0f - c;

    float x = vec.x;
    float y = vec.y;
    float z = vec.z;

    // Calculate the rotated vector using the Rodrigues' formula
    float newX = (x * (t * normalizedAxis.x * normalizedAxis.x + c) +
                  y * (t * normalizedAxis.x * normalizedAxis.y - s * normalizedAxis.z) +
                  z * (t * normalizedAxis.x * normalizedAxis.z + s * normalizedAxis.y));

    float newY = (x * (t * normalizedAxis.x * normalizedAxis.y + s * normalizedAxis.z) +
                  y * (t * normalizedAxis.y * normalizedAxis.y + c) +
                  z * (t * normalizedAxis.y * normalizedAxis.z - s * normalizedAxis.x));

    float newZ = (x * (t * normalizedAxis.x * normalizedAxis.z - s * normalizedAxis.y) +
                  y * (t * normalizedAxis.y * normalizedAxis.z + s * normalizedAxis.x) +
                  z * (t * normalizedAxis.z * normalizedAxis.z + c));

    return Vector3D(newX, newY, newZ);
}

Vector3D Vector3D::Rotation(const Vector3D &vec, const Vector3D &axis, const float angle)
{
    
    float cosA = std::cos(angle);
    float sinA = std::sin(angle);

    // Create temporary copies of the input vectors
    Vector3D tempVec = vec;
    Vector3D tempAxis = axis;

    // Calculate the cross product between the axis and the vector
    Vector3D crossProduct = Vector3D::Cross(tempAxis, tempVec);

    // Calculate the dot product between the axis and the vector
    float dotProduct = Vector3D::Dot(tempAxis, tempVec);

    // Perform the rotation using the temporary copies
    Vector3D rotation = tempVec * cosA + tempAxis * (dotProduct * (1.0f - cosA)) + crossProduct * sinA;

    return rotation;

}

Vector3D Vector3D::UP()
{
    return Vector3D(0.0f,1.0f,0.0f);
}

Vector3D Vector3D::RIGHT()
{
    return Vector3D(1.0f,0.0f,0.0f);
}

Vector3D Vector3D::FORWARD()
{
    return Vector3D(0.0f,0.0f,1.0f);
}

Vector3D Vector3D::INVERT(const Vector3D & vec)
{
    return Vector3D(-vec.x,-vec.y,-vec.z);

}

float Vector3D::DistanceVec(const Vector3D &v1, const Vector3D &v2)
{
    
    float dx = v1.x - v2.x;
    float dy = v1.y - v2.y;
    float dz = v1.z - v2.z;

    return std::sqrt((dx * dx) + (dy * dy) + (dz * dz));

}


std::ostream &operator<<(std::ostream &stream, const Vector3D &vec)
{
    stream << "Vector3D(" << vec.x << "," << vec.y << "," << vec.z << ")";
    return stream;
}





