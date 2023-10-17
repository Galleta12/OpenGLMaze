#pragma once

#include <iostream>
#include <cmath>

class Point{
    public:
        float x,y,z;


        Point();
        Point(float x, float y, float z);
        ~Point();
        
        Point operator+(const Point& p);
        Point operator-(const Point& p);
};

