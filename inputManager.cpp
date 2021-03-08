#include <iostream>
#include "inputManager.h"
#include "draw.h"

Draw Draw::s_drawInstance;

INPUT InputManager::translateInputCode(int sdlKeycode)
{
    switch(sdlKeycode)
    {
        case(SDLK_ESCAPE):
            return I_KESC;
        case(SDLK_a):
        case(SDLK_LEFT):
            return I_KLEFT;
        case(SDLK_d):
        case(SDLK_RIGHT):
            return I_KRIGHT;
        case(SDLK_w):
        case(SDLK_UP):
            return I_KUP;
        case(SDLK_s):
        case(SDLK_DOWN):
            return I_KDOWN;
        case(SDL_BUTTON_LEFT):
            return I_MLEFT;
        case(SDL_BUTTON_RIGHT):
            return I_MRIGHT;
        default:
            return I_UNDEFINED;
    }
}

bool InputManager::update()
{
    while(SDL_PollEvent(&e))
    {
        switch(e.type)
        {
            case(SDL_QUIT):
            {
                quit = true;
                break;
            }
            case(SDL_KEYDOWN):
            {
                /* key presses */
                if(keyStillDown(I_KLEFT) || keyDown(I_KLEFT))
                    s_draw.setRenderElem(TEX_ARROW, 0.0, SDL_FLIP_NONE); 
                if(keyStillDown(I_KRIGHT) || keyDown(I_KRIGHT))
                    s_draw.setRenderElem(TEX_ARROW, 180.0, SDL_FLIP_NONE); 
                if(keyStillDown(I_KUP) || keyDown(I_KUP))
                    s_draw.setRenderElem(TEX_ARROW, 90.0, SDL_FLIP_NONE); 
                if(keyStillDown(I_KDOWN) || keyDown(I_KDOWN))
                    s_draw.setRenderElem(TEX_ARROW, 270.0, SDL_FLIP_NONE); 

                input[translateInputCode(e.key.keysym.sym)] = true;

                break;
            }
            case(SDL_KEYUP):
            {
                /* key releases */
                if(keyUp(I_KESC))
                    quit = true;

                input[translateInputCode(e.key.keysym.sym)] = false;

                break;
            }
            case(SDL_MOUSEBUTTONDOWN):
            {
                if(mouseStillDown(I_MLEFT) || mouseDown(I_MLEFT))
                    s_draw.setRenderElem(TEX_MOUSE, 0.0, SDL_FLIP_NONE);
                if(mouseStillDown(I_MRIGHT) || mouseDown(I_MRIGHT))
                    s_draw.setRenderElem(TEX_MOUSE, 0.0, SDL_FLIP_HORIZONTAL);

                input[translateInputCode(e.button.button)] = true;

                break;
            }
            case(SDL_MOUSEBUTTONUP):
            {
                input[translateInputCode(e.button.button)] = false;
                break;
            }
        }
    }

    return true;
}

bool InputManager::noInput()
{
    for(int i = 0; i < (sizeof(input)/sizeof(bool)); i++)
    {
        if(input[i])
            return false;
    }
    return true;
}

bool InputManager::keyDown(int iKeyIndex)
{
    bool ret = false;
    if(!input[iKeyIndex] && (translateInputCode(e.key.keysym.sym) == iKeyIndex))
        ret = true;
    return ret;
}
bool InputManager::keyStillDown(int iKeyIndex)
{
    bool ret = false;
    if(input[iKeyIndex] && (translateInputCode(e.key.keysym.sym) == iKeyIndex))
        ret = true;
    return ret;
}
bool InputManager::keyUp(int iKeyIndex)
{
    bool ret = false;
    if(input[iKeyIndex] && (translateInputCode(e.key.keysym.sym) == iKeyIndex))
        ret = true;
    return ret;
}
bool InputManager::keyStillUp(int iKeyIndex)
{
    bool ret = false;
    if(!input[iKeyIndex])
        ret = true;
    return ret;
}

bool InputManager::mouseDown(int iButton)
{
    bool ret = false;
    if(!input[iButton] && (translateInputCode(e.button.button) == iButton))
        ret = true;
    return ret;
}
bool InputManager::mouseStillDown(int iButton)
{

    bool ret = false;
    if(input[iButton] && (translateInputCode(e.button.button) == iButton))
        ret = true;
    return ret;
}
bool InputManager::mouseUp(int iButton)
{
    bool ret = false;
    if(input[iButton] && (translateInputCode(e.button.button) == iButton))
        ret = true;
    return ret;
}
bool InputManager::mouseStillUp(int iButton)
{
    bool ret = false;
    if(!input[iButton])
        ret = true;
    return ret;
}
