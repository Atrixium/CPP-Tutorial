#include "mover.h"

mover::mover(float posX, float posY, float velX, float velY, float accX, float accY, float maxS)
{
    position.setX(posX);
    position.setY(posY);
    velocity.setX(velX);
    velocity.setY(velY);
    acceleration.setX(accX);
    acceleration.setY(accY);
    maxSpeed = maxS;
}

mover::~mover()
{
    SDL_DestroyTexture(image);
}

void mover::edgeCollision()
{
    if (position.getX() > SCREEN_WIDTH)
        position.setX(0);
    else if(position.getX() < 0)
        position.setX(SCREEN_WIDTH);

    if (position.getY() > SCREEN_HEIGHT)
        position.setY(0);
    else if (position.getY() < 0)
        position.setY(SCREEN_HEIGHT);
}

void mover::display(SDL_Renderer* ren)
{
    renderTexture(image, ren, position.getX(), position.getY());
}

void mover::loadImage(std::string imagePath, SDL_Renderer*& ren)
{
        image = loadTexture(imagePath,ren);
}

void mover::update()
{
    velocity.add(acceleration);
    velocity.limit(maxSpeed);
    position.add(velocity);
    acceleration.mult(0);
}

void mover::applyForce(vec2 force)
{
    acceleration.add(force);
}
