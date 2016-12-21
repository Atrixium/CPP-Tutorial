#include <SDL2/SDL.h>
#include <iostream>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void logSDLError(std::ostream &os, const std::string &msg);

SDL_Texture* loadTexture(const std::string &path, SDL_Renderer *renderer);

void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y);

void cleanup(SDL_Texture *tex1, SDL_Texture *tex2 = nullptr, SDL_Renderer *ren = nullptr, SDL_Window *win = nullptr);


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

    SDL_Texture *background = loadTexture("Images/background.bmp", renderer);
    SDL_Texture *image = loadTexture("Images/image.bmp",renderer);
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

    int bW, bH;
    SDL_QueryTexture(background,NULL,NULL,&bW, &bH);
    for (int i = 0; i < SCREEN_HEIGHT; i = i + bH)
    {
        for (int j = 0; j < SCREEN_WIDTH; j = j + bW)
        {
            renderTexture(background, renderer, j, i);
        }
    }
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);


    return 0;
}


void logSDLError(std::ostream &os, const std::string &msg)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
}

SDL_Texture* loadTexture(const std::string &path, SDL_Renderer *renderer)
{
    SDL_Texture *texture = nullptr;

    SDL_Surface *bmp = SDL_LoadBMP(path.c_str());
    if (bmp != nullptr)
    {
        texture = SDL_CreateTextureFromSurface(renderer, bmp);
        SDL_FreeSurface(bmp);
        if (texture == nullptr)
        {
            logSDLError(std::cout, "SDL_CreateTextureFromSurface");
        }
    }
    else
    {
        logSDLError(std::cout, "SDL_LoadBMP");
    }
    return texture;
}

void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y)
{
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;

    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(renderer, texture, NULL, &dst);
}

void cleanup(SDL_Texture *tex1, SDL_Texture *tex2, SDL_Renderer *ren, SDL_Window *win)
{
    SDL_DestroyTexture(tex1);
    if(tex1!= nullptr)
    SDL_DestroyTexture(tex2);
    if(ren != nullptr)
    SDL_DestroyRenderer(ren);
    if(win != nullptr)
    SDL_DestroyWindow(win);
}
