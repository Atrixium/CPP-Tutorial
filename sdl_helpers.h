#ifndef SDL_HELPERS_H
#define SDL_HELPERS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

bool initializeSDL(SDL_Window*& win, SDL_Renderer*& ren);

void logSDLError(std::ostream &os, const std::string &msg);

SDL_Texture* loadTexture(const std::string &path, SDL_Renderer* renderer);

void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y);
void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, int w, int h);

#endif // SDL_HELPERS_H
