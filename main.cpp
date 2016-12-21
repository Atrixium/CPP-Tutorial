#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <math.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class vec2
{
    float x;
    float y;

public:
    float getX() {return x;};
    float getY() {return y;};
    void setX(float i) {x = i ;};
    void setY(float i) {y = i ;};

    void add(vec2 vec);
    void mult(int scaler);
    void sub(vec2 vec);
    float getMag() {return sqrt( (x*x) + (y*y) );};
    void setMag(float mag);
    void normalize();
};


void logSDLError(std::ostream &os, const std::string &msg);

SDL_Texture* loadTexture(const std::string &path, SDL_Renderer *renderer);

void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y);
void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, int w, int h);

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

    vec2 v;
    v.setX(1);
    v.setY(1);

    std::cout << v.getX() << "," << v.getY() << std::endl;

    v.setMag(25);

    std::cout << v.getX() << "," << v.getY() << std::endl;

    SDL_RenderPresent(renderer);
    //SDL_Delay(2000);

    SDL_DestroyTexture(background);
    SDL_DestroyTexture(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


void logSDLError(std::ostream &os, const std::string &msg)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
}

SDL_Texture* loadTexture(const std::string &path, SDL_Renderer *renderer)
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

void vec2::add(vec2 vec)
{
    this->x += vec.x;
    this->y += vec.y;

}

void vec2::mult(int scaler)
{
    this->x *= scaler;
    this->y *= scaler;
}

void vec2::sub(vec2 vec)
{
    this->x -= vec.x;
    this->y -= vec.y;
}

void vec2::normalize()
{
    float mag = this->getMag();
    this->x = this->x / mag;
    this->y = this->y / mag;
}

void vec2::setMag(float mag)
{
    this->normalize();
    this->mult(mag);
}
