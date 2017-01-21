#include "mover.h"

mover::mover(float posX, float posY, float velX, float velY, float accX, float accY, float maxS, float _mass)
{
    mover::moverList.push_back(this);
    id = mover::moverList.size();
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
    mover::moverList.begin()+id;
}

void mover::edgeCollision()
{
    if ( (position.getX() + width >= SCREEN_WIDTH) )
    {
        position.setX(SCREEN_WIDTH - width);
        velocity.setX(velocity.getX() * -1);
    }
    else if (position.getX() <= 0)
    {
        position.setX(0);
        velocity.setX(velocity.getX() * -1);
    }

    if ( (position.getY() + height >= SCREEN_HEIGHT) )
    {
        position.setY(SCREEN_HEIGHT - height);
        velocity.setY(velocity.getY() * -1);
    }
    else if (position.getY() <= 0)
    {
        position.setY(0);
        velocity.setY(velocity.getY() * -1);
    }

}

void mover::objectCollision(mover* m)
{
    //circle-based collision detection
    vec2 aCenter( (position.getX()) + (width / 2), (position.getY()) + (width / 2) );
    vec2 bCenter( (m->position.getX()) + (m->width / 2), (m->position.getY()) + (m->height / 2) );
    vec2 distance = vec2::sub(aCenter,bCenter);

    if ( distance.getMag() < ( (width / 2) + (m->width / 2) ) )
    {
        std::cout << "Collision detected between " << id << " & " << m->id << std::endl;
        vec2 momentum(0,0);
        momentum.add(m->velocity);
        momentum.mult(m->mass);
        distance.setMag(momentum.getMag()/2);
        applyForce(distance);
        distance.mult(-1);
        m->applyForce(distance);
    }
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

std::vector<mover*> mover::moverList;
