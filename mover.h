#ifndef MOVER_H
#define MOVER_H

#include "vec2.h"
#include "sdl_helpers.h"
#include "globals.h"
#include <SDL2/SDL.h>
#include <string>
#include <vector>

class mover
{
public:
    static std::vector<mover*> moverList;
    int id;
    vec2 position;
    vec2 velocity;
    vec2 acceleration;
    float maxSpeed;
    float mass;
    int width;
    int height;
private:
    SDL_Texture* image;

public:
    mover(float posX=1, float posY=1, float velX=0, float velY=0, float AccX=0, float AccY=0, float maxS=10, float _mass=1);
    ~mover();

    int getWidth(){return width;};
    int getHeight(){return height;};
    int setWidth(int w){width=w;};
    int setHeight(int h){height=h;};
    void edgeCollision();
    void objectCollision(mover*);
    void display(SDL_Renderer* ren);
    void loadImage(std::string imagePath, SDL_Renderer*& ren);
    void update();
    void applyForce(vec2 force);

};

#endif // MOVER_H
