#include "vec2.h"

vec2::vec2()
{
    this->x = 1;
    this->y = 1;
}

vec2::vec2(float x, float y)
{
    this->x = x;
    this->y = y;
}

void vec2::add(vec2 vec)
{
    this->x += vec.x;
    this->y += vec.y;

}
vec2 vec2::add(vec2 a, vec2 b)
{
    vec2 result = vec2(a.getX() + b.getX(), a.getY() + b.getY());
    return result;
}

void vec2::mult(float scaler)
{
    this->x *= scaler;
    this->y *= scaler;
}

void vec2::div(float div)
{
    if (div != 0)
    {
        this->x /= div;
        this->y /= div;
    }
}

void vec2::sub(vec2 vec)
{
    this->x -= vec.x;
    this->y -= vec.y;
}

vec2 vec2::sub(vec2 a, vec2 b)
{
    vec2 result = vec2(a.getX() - b.getX(), a.getY() - b.getY());
    return result;
}

void vec2::normalize()
{
    float mag = this->getMag();
    if (mag)
        div(mag);
}

void vec2::setMag(float mag)
{
    if(this->getMag() != 0)
    {
        this->normalize();
        this->mult(mag);
    }
    else if( mag > 0 )
    {
        this->x = 1 * mag;
        this->y = 1 * mag;
    }
}

void vec2::limit(float limit)
{
    if (this->getMag() > limit)
        this->setMag(limit);
}
