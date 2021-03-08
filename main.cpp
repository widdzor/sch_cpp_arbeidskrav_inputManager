#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "inputManager.h"
#include "draw.h"

#define WW 640
#define WH 480

InputManager InputManager::s_InputManager;
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

    SDL_Event e;
    InputManager& s_input = InputManager::getInstance();
    Draw& s_draw = Draw::getInstance();
    s_draw.setWinRef(win);
    s_draw.initTextures(rend);
    s_draw.setRenderElem(TEX_NONE, 0.0, SDL_FLIP_NONE);
    
    SDL_SetRenderDrawColor(rend, 64, 32, 128, 255);
    while(!s_input.shouldQuit())
    {
        s_input.update();

        SDL_RenderClear(rend);

        s_draw.renderElem(rend);

        SDL_RenderPresent(rend);
    }

    s_draw.freeTextures();
    IMG_Quit();
    SDL_Quit();
    return 0;
}
