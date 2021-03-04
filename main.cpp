#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "inputManager.h"

#define WW 640
#define WH 480

bool quit = false;

SDL_Texture *createTexture(SDL_Renderer *renderer, const char* filename);
int main()
{
    // Initialize SDL, Only need video subsystem.
    if(SDL_Init(SDL_INIT_VIDEO))
    {
        std::cout << "SDL_Init: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window *win = SDL_CreateWindow(
            "Arbeidskrav - InputManager",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            WW, WH, SDL_WINDOW_SHOWN);
    if(!win)
    {
        std::cout << "SDL_CreateWindow: " << SDL_GetError() << std::endl;
        SDL_Quit();
        
        return -1;
    }

    SDL_Renderer *rend = SDL_CreateRenderer(
            win, -1, SDL_RENDERER_ACCELERATED);
    if(!rend)
    {
        std::cout << "SDL_CreateRenderer: " << SDL_GetError() << std::endl;
        SDL_Quit();

        return -1;
    }

    if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        std::cout << "IMG_Init: " << IMG_GetError() << std::endl;
        SDL_Quit();

        return -1;
    }

    SDL_Texture *texNone  = createTexture(rend, "res/none.png");
    SDL_Texture *texArrow = createTexture(rend, "res/arrowkeys.png");
    SDL_Texture *texMouse = createTexture(rend, "res/mouseclick.png");
    SDL_Rect rectTexArrow = {158, 0, 158, 254};
    SDL_Rect tmpRect;

    SDL_Event e;
    while(!quit)
    {
        SDL_PollEvent(&e);
        switch(e.type)
        {
            case(SDL_KEYDOWN):
                switch(e.key.keysym.sym)
                    case(SDLK_ESCAPE):
            case(SDL_QUIT):
            {
                quit = true;
                break;
            }
        }

        SDL_SetRenderDrawColor(rend, 128, 128, 64, 255);
        SDL_RenderClear(rend);

        SDL_RenderCopy(rend, texArrow, NULL, NULL);

        SDL_RenderPresent(rend);
    }

    IMG_Quit();
    SDL_Quit();
    return 0;
}

SDL_Texture *createTexture(SDL_Renderer *renderer, const char* filename)
{
    SDL_Surface *temp = IMG_Load(filename);
    if(!temp)
    {
        std::cout << "IMG_Load: " << IMG_GetError() << std::endl;
        return NULL;
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, temp);
    if(!tex)
    {
        std::cout << "SDL_CreateTextureFromSurface: " << SDL_GetError() << std::endl;
        return NULL;
    }

    SDL_FreeSurface(temp);
    return tex;
}
