#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include "core/Constants.hpp"

class Game {
public:
    bool running = true;
    SDL_Window* win = nullptr;
    SDL_Renderer* ren = nullptr;

    Game();
    ~Game();
};

#endif