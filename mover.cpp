#include "mover.h"

mover::mover(float posX, float posY, float velX, float velY, float accX, float accY, float maxS, float _mass)
{
    position.setX(posX);
    position.setY(posY);
    velocity.setX(velX);
    velocity.setY(velY);
    acceleration.setX(accX);
    acceleration.setY(accY);
    maxSpeed = maxS;
    mass = _mass;
}

mover::~mover()
{
    SDL_DestroyTexture(image);
}

void mover::edgeCollision()
{
    if ( (position.getX() + width >= SCREEN_WIDTH) || (position.getX() <= 0) )
        velocity.setX(velocity.getX() * -1);

    if ( (position.getY() + height >= SCREEN_HEIGHT) || (position.getY() <= 0) )
        velocity.setY(velocity.getY() * -1);
}

void mover::display(SDL_Renderer* ren)
{
    renderTexture(image, ren, position.getX(), position.getY(), width, height);
}

void mover::loadImage(std::string imagePath, SDL_Renderer*& ren)
{
        image = loadTexture(imagePath,ren);
        SDL_QueryTexture(image, NULL, NULL, &width, &height);
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
    force.div(mass);
    acceleration.add(force);
}
