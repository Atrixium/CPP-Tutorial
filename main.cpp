#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "sdl_helpers.h"
#include "vec2.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


SDL_Texture* loadTexture(const std::string &path, SDL_Renderer *renderer);


int main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) !=0)
    {
        logSDLError(std::cout, "SDL Init");
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Hello World", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        logSDLError(std::cout, "SDL_CreateWindow");
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        SDL_DestroyWindow(window);
        logSDLError(std::cout, "SDL_CreateRenderer");
        SDL_Quit();
        return 1;
    }

    SDL_Event event;


    //End of SDL boilerplate inits

    if( (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        logSDLError(std::cout, "IMG_init");
        SDL_Quit();
        return 1;
    }

    //End of SDL module inits

    bool quit = false;

    //load textures

    SDL_Texture *background = loadTexture("Images/background.png", renderer);
        SDL_Texture *image = loadTexture("Images/image.png",renderer);
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

        //int mouseX = SCREEN_WIDTH / 2;
        //int mouseY = SCREEN_HEIGHT / 2;

        vec2 position;
        position.setX(SCREEN_WIDTH / 2);
        position.setY(SCREEN_HEIGHT / 2);

        vec2 velocity;
        velocity.setMag(5);

        int iW, iH;
        SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
        SDL_SetRenderDrawColor(renderer, 255,255,255,255);

    while(!quit)
    {

        //vector debug
//        std::cout << "Position.X: " << position.getX() << std::endl;
//        std::cout << "Position.Y: " << position.getY() << std::endl;
//        std::cout << "Velocity.X: " << velocity.getX() << std::endl;
//        std::cout << "Velocity.Y: " << velocity.getY() << std::endl;
        position.add(velocity);

        if (position.getX() >= SCREEN_WIDTH - iW | position.getX() <= 0)
        {
            velocity.setX(velocity.getX() *-1);
        }
        if (position.getY() >= SCREEN_HEIGHT - iH| position.getY() <= 0)
        {
            velocity.setY(velocity.getY() *-1);
        }

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
                            velocity.setX(velocity.getX() + 1);
                            velocity.setY(velocity.getY() + 1);
                            break;

                        case SDLK_z:
                            velocity.setX(velocity.getX() - 1);
                            velocity.setY(velocity.getY() - 1);
                            break;
                    }
                    break;
//                case SDL_MOUSEMOTION:
//                    mouseX = event.motion.x;
//                    mouseY = event.motion.y;
//                    break;
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
