#pragma once

#include <iostream>
#include <cmath>

class RadToDegree{


    private:
        //private constractor to prevent initialization      
        RadToDegree(){}
    public:
        //initialize static inside the class
        static constexpr float PI = 3.14159265358979323846f;

        static float convert(float angleRad){
            return (angleRad * 180.0f)/PI;
        }

        
        // Convert degrees to radians
        static float ToRadians(float angleDeg) {
            return (angleDeg * PI) / 180.0f;
        }


};