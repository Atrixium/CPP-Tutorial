#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "sdl_helpers.h"
#include "vec2.h"
#include "globals.h"
#include "mover.h"
#include <memory>


int main(int argc, char **argv)
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event event;

    if (!initializeSDL(window, renderer))
        return 1;


    //load textures

    SDL_Texture* background = loadTexture("Images/background.png", renderer);
    if(background == nullptr)
    {
        logSDLError(std::cout, "loadTexture");
        SDL_DestroyTexture(background);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

        srand(time(NULL));

        SDL_SetRenderDrawColor(renderer, 255,255,255,255);

        for(int i=0; i<5; i++)
        {
            new mover();
        }


        for(int i=0; i<mover::moverList.size();i++)
        {
            mover::moverList[i]->position.setX(rand() % 640);
            mover::moverList[i]->mass = rand() % 100+1;
            mover::moverList[i]->loadImage("Images/ball.png", renderer);
            mover::moverList[i]->setHeight(mover::moverList[i]->mass+25);
            mover::moverList[i]->setWidth(mover::moverList[i]->height);
        }


        vec2 wind(10,0);

    bool mousePressed = false;

    bool quit = false;
    while(!quit)

    {

        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {

                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_q:
                            quit = true;
                            break;

                        case SDLK_x:
                            quit = true;
                            break;

                        case SDLK_a:
                            //velocity.setMag(velocity.getMag() + 1);
                            break;

                        case SDLK_z:
                            //velocity.setMag(velocity.getMag() - 1);
                            break;
                        case SDLK_SPACE:
                            break;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    //mouse.setX(event.motion.x);
                    //mouse.setY(event.motion.y);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    mousePressed = true;
                    break;
                case SDL_MOUSEBUTTONUP:
                    mousePressed = false;
                    break;
            }
        }

        SDL_RenderClear(renderer);



        for(int i=0; i<mover::moverList.size(); i++)
        {
            std::cout << "Mover object: " << i << std::endl;

            vec2 gravity(0,GRAV_CONSTANT*mover::moverList[i]->mass);
            mover::moverList[i]->applyForce(gravity);
            if(mousePressed)
                mover::moverList[i]->applyForce(wind);
            mover::moverList[i]->update();
            mover::moverList[i]->display(renderer);
            mover::moverList[i]->edgeCollision();
            for(int j=0; j< mover::moverList.size(); j++)
            {
                if( mover::moverList[i]->id != mover::moverList[j]->id )
                    mover::moverList[i]->objectCollision(mover::moverList[j]);
            }

        }


        std::cout << "Items in moverList: " << mover::moverList.size() << std::endl;

        SDL_RenderPresent(renderer);

    }
    //Destroy all created objects
    SDL_DestroyTexture(background);

    //Destroy SDL Main objects and quit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << "Number of elements in moverList: " << mover::moverList.size() << std::endl;

    return 0;
}
