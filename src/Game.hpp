#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "core/Constants.hpp"
#include "core/Enums.hpp"
#include "core/Vec2.hpp"
#include "engine/InputHandler.hpp"
#include "ui/HUD.hpp"

class Game {
public:
    bool running = true;
    GameState state = GameState::MENU;
    SDL_Window* win = nullptr;
    SDL_Renderer* ren = nullptr;
    TTF_Font *font = nullptr, *fontL = nullptr;

    std::vector<std::vector<Tile>> map;
    InputHandler input;
    HUD hud;

    Vec2 cam = {0, 0};

    Game();
    ~Game();
    void init();
    void generateLevel();
    void handleInput();
    void render();

    void loop();
};

#endif