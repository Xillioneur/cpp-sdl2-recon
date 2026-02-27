#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "core/Constants.hpp"
#include "core/Enums.hpp"
#include "engine/InputHandler.hpp"
#include "ui/HUD.hpp"

class Game {
public:
    bool running = true;
    GameState state = GameState::MENU;
    SDL_Window* win = nullptr;
    SDL_Renderer* ren = nullptr;
    TTF_Font *font = nullptr, *fontL = nullptr;

    InputHandler input;
    HUD hud;

    Game();
    ~Game();
    void handleInput();
    void render();

    void loop();
};

#endif