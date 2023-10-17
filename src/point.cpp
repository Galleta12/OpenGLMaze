#include "Point.h"

Point::Point():x(0.0f),y(0.0f),z(0.0f)
{
}

Point::Point(float x, float y, float z)
{
    this->x=x;
    this->y=y;
    this->z=z;
}

Point::~Point()
{

}

Point Point::operator+(const Point &p)
{
    return Point(x + p.x,y + p.y, z + p.z);   
}

Point Point::operator-(const Point &p)
{
    return Point(x + p.x,y + p.y, z + p.z);   
}
