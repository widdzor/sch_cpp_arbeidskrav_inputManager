#include <iostream>
#include "draw.h"
#include "inputManager.h"

void Draw::setWinRef(SDL_Window* w)
{
    win = w;
}

SDL_Texture *Draw::createTexture(SDL_Renderer *rend, const char* filename)
{
    SDL_Surface *temp = IMG_Load(filename);
    if(!temp)
    {
        std::cout << "IMG_Load: " << IMG_GetError() << std::endl;
        return NULL;
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(rend, temp);
    if(!tex)
    {
        std::cout << "SDL_CreateTextureFromSurface: " << SDL_GetError() << std::endl;
        return NULL;
    }

    SDL_FreeSurface(temp);
    return tex;
}

void Draw::initTextures(SDL_Renderer* rend)
{
    textures[TEX_NONE] = createTexture(rend, "res/none.png");
    textures[TEX_ARROW] = createTexture(rend, "res/arrowkeys.png");
    textures[TEX_MOUSE] = createTexture(rend, "res/mouseclick.png");
}
void Draw::freeTextures()
{
    for(int i = 0; i < 3; i++)
    {
        SDL_DestroyTexture(textures[i]);
    }
}

void Draw::setRenderElem(TexNum n, double angle, SDL_RendererFlip flip)
{
    toDraw.n = n;
    int winW, winH;
    SDL_GetWindowSize(win, &winW, &winH);
    int srcW, srcH;
    SDL_QueryTexture(textures[toDraw.n], NULL, NULL, &toDraw.rctDst.w, &toDraw.rctDst.h);
    toDraw.rctDst.x = (winW/2) - (toDraw.rctDst.w/2);
    toDraw.rctDst.y = (winH/2) - (toDraw.rctDst.h/2);
    toDraw.angle = angle;
    toDraw.flip = flip;
    toDraw.center.x = toDraw.rctDst.w/2;
    toDraw.center.y = toDraw.rctDst.h/2;
}

InputManager& s_input = InputManager::getInstance();
void Draw::renderElem(SDL_Renderer* rend)
{
    if(s_input.noInput())
        setRenderElem(TEX_NONE, 0.0, SDL_FLIP_NONE);
    SDL_RenderCopyEx(
            rend,
            textures[toDraw.n],
            NULL,
            ((toDraw.rctDst.w) && (toDraw.rctDst.h)) ? &(toDraw.rctDst) : NULL,
            toDraw.angle, NULL,
            toDraw.flip);
}
