#ifndef VEC2_H
#define VEC2_H

#include <math.h>

class vec2
{
    float x;
    float y;

public:
    float getX() {return x;};
    float getY() {return y;};
    void setX(float i) {x = i ;};
    void setY(float i) {y = i ;};

    void add(vec2 vec);
    void mult(int scaler);
    void sub(vec2 vec);
    float getMag() {return sqrt( (x*x) + (y*y) );};
    void setMag(float mag);
    void normalize();
};

#endif
