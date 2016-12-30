#include "vec2.h"

void vec2::add(vec2 vec)
{
    this->x += vec.x;
    this->y += vec.y;

}

void vec2::mult(int scaler)
{
    this->x *= scaler;
    this->y *= scaler;
}

void vec2::sub(vec2 vec)
{
    this->x -= vec.x;
    this->y -= vec.y;
}

void vec2::normalize()
{
    float mag = this->getMag();
    this->x = this->x / mag;
    this->y = this->y / mag;
}

void vec2::setMag(float mag)
{
    this->normalize();
    this->mult(mag);
}
