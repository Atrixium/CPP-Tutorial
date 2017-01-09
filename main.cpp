#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "sdl_helpers.h"
#include "vec2.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool initializeSDL(SDL_Window*& win, SDL_Renderer*& ren);


int main(int argc, char **argv)
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event event;

    if (!initializeSDL(window, renderer))
        return 1;


    //load textures

    SDL_Texture* background = loadTexture("Images/background.png", renderer);
        SDL_Texture* image = loadTexture("Images/image.png", renderer);
        if(background == nullptr || image == nullptr)
        {
            logSDLError(std::cout, "loadTexture");
            SDL_DestroyTexture(background);
            SDL_DestroyTexture(image);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            return 1;
        }

        vec2 mouse;

        vec2 position;
        position.setX(SCREEN_WIDTH / 2);
        position.setY(SCREEN_HEIGHT / 2);

        vec2 velocity;
        velocity.setMag(5);

        int iW, iH;
        SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
        SDL_SetRenderDrawColor(renderer, 255,255,255,255);

    bool quit = false;
    while(!quit)
    {

//        //vector debug
//        std::cout << "Position.X: " << position.getX() << " " << "Position.Y: " << position.getY() << std::endl;
//        std::cout << "Velocity.X: " << velocity.getX() << " " << "Velocity.Y: " << velocity.getY() << std::endl;
//        std::cout << "Velocity.Mag: " <<velocity.getMag() << std::endl << std::endl;
//        std::cout << "Mouse X: " << mouse.getX() << " " << "Mouse Y: " << mouse.getY() << std::endl;

        vec2 acceleration = vec2::sub(mouse, position);
        acceleration.normalize();
        acceleration.mult(.5);

        velocity.add(acceleration);
        position.add(velocity);
        velocity.limit(10);

//        if ( (position.getX() >= (SCREEN_WIDTH - iW) ) | (position.getX() <= 0))
//            velocity.setX(velocity.getX() *-1);
//        if ( (position.getY() >= (SCREEN_HEIGHT - iH) )| (position.getY() <= 0))
//            velocity.setY(velocity.getY() *-1);

        if (position.getX() > SCREEN_WIDTH)
            position.setX(0);
        else if(position.getX() < 0)
            position.setX(SCREEN_WIDTH);

        if (position.getY() > SCREEN_HEIGHT)
            position.setY(0);
        else if (position.getY() < 0)
            position.setY(SCREEN_HEIGHT);


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
                            velocity.setMag(velocity.getMag() + 1);
                            break;

                        case SDLK_z:
                            velocity.setMag(velocity.getMag() - 1);
                            break;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    mouse.setX(event.motion.x);
                    mouse.setY(event.motion.y);
                    break;
            }
        }

        SDL_RenderClear(renderer);
        renderTexture(image, renderer, position.getX(), position.getY());

        SDL_RenderPresent(renderer);

    }
    //destroy all created objects
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(image);
    //Destroy SDL Main objects and quit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

bool initializeSDL(SDL_Window*& win, SDL_Renderer*& ren)
{
    if (SDL_Init(SDL_INIT_VIDEO) !=0)
    {
        logSDLError(std::cout, "SDL Init");
        return false;
    }

    win = SDL_CreateWindow("Hello World", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (win == nullptr)
    {
        logSDLError(std::cout, "SDL_CreateWindow");
        SDL_Quit();
        return false;
    }

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr)
    {
        SDL_DestroyWindow(win);
        logSDLError(std::cout, "SDL_CreateRenderer");
        SDL_Quit();
        return false;
    }

    if( (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        logSDLError(std::cout, "IMG_init");
        SDL_Quit();
        return 1;
    }

    return true;
}
