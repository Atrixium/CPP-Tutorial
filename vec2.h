#ifndef VEC2_H
#define VEC2_H

#include <math.h>

class vec2
{
    float x;
    float y;

public:
    vec2();
    vec2(float,float);
    float getX() {return x;};
    float getY() {return y;};
    void setX(float i) {x = i ;};
    void setY(float i) {y = i ;};

    void add(vec2 vec);
    static vec2 add(vec2 a, vec2 b);
    void sub(vec2 vec);
    static vec2 sub(vec2 a, vec2 b);
    void mult(float scaler);
    void div(float div);
    float getMag() {return sqrt( (x*x) + (y*y) );};
    void setMag(float mag);
    void normalize();
    void limit(float limit);
};

#endif
