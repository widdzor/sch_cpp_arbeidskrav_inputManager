#ifndef DRAW_H
#define DRAW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <queue>

enum TexNum
{
    TEX_NONE, TEX_ARROW, TEX_MOUSE
};
struct RenderElem
{
    TexNum n;
    SDL_Rect rctDst;
    SDL_Point center;
    double angle;
    SDL_RendererFlip flip;
};

class Draw
{
public:
    Draw(const Draw&) = delete;

    static Draw& getInstance()
    {
        return s_drawInstance;
    }

    void setWinRef(SDL_Window *w);
    void initTextures(SDL_Renderer* rend);
    void freeTextures();
    SDL_Texture *createTexture(SDL_Renderer *rend, const char* filename);
    void setRenderElem(TexNum n, double angle, SDL_RendererFlip flip);
    void renderElem(SDL_Renderer* rend);

private:
    SDL_Window* win;
    SDL_Texture *textures[3];
    RenderElem toDraw;

    Draw() {}
    static Draw s_drawInstance;
};


#endif // DRAW_H
