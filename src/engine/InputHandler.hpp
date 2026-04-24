
#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <SDL2/SDL.h>

class InputHandler {
    public:
        bool keys[SDL_NUM_SCANCODES] = {false};
        bool lastKeys[SDL_NUM_SCANCODES] = {false};
        Vec2 mPos;
    
        void update() {
            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) exit(0);
                if (e.type == SDL_KEYDOWN) keys[e.key.keysym.scancode] = true;
                if (e.type == SDL_KEYUP) keys[e.key.keysym.scancode] = false;
                if (e.type == SDL_MOUSEMOTION) {
                    mPos.x = (float)e.motion.x;
                    mPos.y = (float)e.motion.y;
                }
            }
        }
        bool isPressed(SDL_Scancode c) const { return keys[c]; }
};

#endif