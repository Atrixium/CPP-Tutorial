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

        mover balls[25];

        for(int i=0; i<25; i++)
        {
            balls[i].mass = rand() % 100 + 1;
            balls[i].loadImage("Images/ball.png", renderer);
            balls[i].setHeight(balls[i].mass + 25);
            balls[i].setWidth(balls[i].height);
        }

        vec2 wind(5,0);

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
//                    ball.applyForce(wind);
//                    ball2.applyForce(wind);
                    for(int i=0; i<25; i++)
                    {
                        balls[i].applyForce(wind);
                    }
                    break;
            }
        }

        SDL_RenderClear(renderer);


        for(int i=0; i<25; i++)
        {
            std::cout << "Iteration : " << i << std::endl;

            vec2 gravity(0,GRAV_CONSTANT*balls[i].mass);
            balls[i].applyForce(gravity);
            balls[i].update();
            balls[i].display(renderer);
            balls[i].edgeCollision();
            std::cout << "ball " << i << "acceleration: " << balls[i].acceleration.getMag() << std::endl;
        }

        SDL_RenderPresent(renderer);

        //std::cout << "balls[1] : " << balls[1].velocity.getMag() << std::endl;

    }
    //destroy all created objects
    SDL_DestroyTexture(background);

    //Destroy SDL Main objects and quit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
