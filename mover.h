#ifndef MOVER_H
#define MOVER_H

#include "vec2.h"
#include "sdl_helpers.h"
#include "globals.h"
#include <SDL2/SDL.h>
#include <string>

class mover
{
public:
    vec2 position;
    vec2 velocity;
    vec2 acceleration;
    float maxSpeed;
private:
    SDL_Texture* image;

public:
    mover(float posX=1, float posY=1, float velX=0, float velY=0, float AccX=0, float AccY=0, float maxS=0);
    ~mover();
    void edgeCollision();
    void display(SDL_Renderer* ren);
    void loadImage(std::string imagePath, SDL_Renderer*& ren);
    void update();

};

#endif // MOVER_H
