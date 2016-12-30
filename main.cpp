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

    if( (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        logSDLError(std::cout, "IMG_init");
        SDL_Quit();
        return 1;
    }

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

    SDL_RenderClear(renderer);

    int scaler = 3;

    int bW, bH;
    SDL_QueryTexture(background,NULL,NULL,&bW, &bH);
    for (int i = 0; i < SCREEN_HEIGHT; i = i + bH / scaler)
    {
        for (int j = 0; j < SCREEN_WIDTH; j = j + bW / scaler)
        {
            renderTexture(background, renderer, j, i, bW / scaler, bH / scaler);
        }
    }

    int iW, iH;
    SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
    renderTexture(image, renderer, SCREEN_WIDTH/2 - iW/2, SCREEN_HEIGHT/2 - iH/2);

    SDL_RenderPresent(renderer);
    SDL_Delay(2000);

    SDL_DestroyTexture(background);
    SDL_DestroyTexture(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
