
#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <SDL2/SDL.h>

class InputHandler {
    public:
        void update() {
            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) exit(0);
            }
        }
};

#endif