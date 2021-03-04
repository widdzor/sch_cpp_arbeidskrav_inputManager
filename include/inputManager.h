#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

class InputManager
{
public:
    // This should implement the Singleton pattern.
    // needs improvements to the header file.
    static InputManager* GetInstance();
    bool Update();

    // Keyboard
    bool KeyDown(int iKeyIndex);
    bool KeyStillDown(int iKeyIndex);
    bool KeyUp(int iKeyIndex);
    bool KeyStillUp(int iKeyIndex);

    // Mouse
    bool MouseDown(int iButton);
    bool MouseStillDown(int iButton);
    bool MouseUp(int iButton);
    bool MouseStillUp(int iButton);

private:
    // Make private helper methods here!
};

#endif //INPUT_MANAGER_H
