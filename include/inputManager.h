#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <SDL2/SDL.h>
#include "draw.h"

enum INPUT
{
    I_KESC, I_KLEFT, I_KRIGHT, I_KUP, I_KDOWN, I_MLEFT, I_MRIGHT, I_UNDEFINED
};
class InputManager
{
public:
    InputManager(const InputManager&) = delete;

    static InputManager& getInstance()
    {
        return s_InputManager;
    }

    bool update();
    bool shouldQuit(){return quit;}

    // Keyboard
    bool keyDown(int iKeyIndex);
    bool keyStillDown(int iKeyIndex);
    bool keyUp(int iKeyIndex);
    bool keyStillUp(int iKeyIndex);
    bool noInput();

    // Mouse
    bool mouseDown(int iButton);
    bool mouseStillDown(int iButton);
    bool mouseUp(int iButton);
    bool mouseStillUp(int iButton);

private:
    InputManager() {}
    static InputManager s_InputManager;
    
    Draw& s_draw = Draw::getInstance();
    bool quit = false;
    SDL_Event e;
    bool input[8] = {0};

    INPUT translateInputCode(int sdlInputCode);
};

#endif //INPUT_MANAGER_H
