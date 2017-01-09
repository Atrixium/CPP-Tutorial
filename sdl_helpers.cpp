#include "sdl_helpers.h"

void logSDLError(std::ostream &os, const std::string &msg)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
}

SDL_Texture* loadTexture(const std::string &path, SDL_Renderer* renderer)
{
    SDL_Texture *texture = IMG_LoadTexture(renderer, path.c_str());
    if (texture == nullptr)
    {
        logSDLError(std::cout, "IMG_LoadTexture");
    }
    return texture;
}

void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y)
{
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    renderTexture(texture, renderer, x, y, w, h);
}

void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, int w, int h)
{
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;

    SDL_RenderCopy(renderer, texture, NULL, &dst);
}
