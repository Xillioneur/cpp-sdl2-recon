#include "Game.hpp"
#include <iostream>

Game::Game() {
    TTF_Init();
    win = SDL_CreateWindow("Recon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    font = TTF_OpenFont("assets/OpenSans-Regular.ttf", 18); 
    if (!font) {
        std::cerr << "Failed to load font: assets/OpenSans-Regular.ttf! SDL_ttf Error: " << TTF_GetError() << std::endl;
        running = false;
        return;
    }
    fontL = TTF_OpenFont("assets/OpenSans-Regular.ttf", 52);
    if (!fontL) {
        std::cerr << "Failed to load large font: assets/OpenSans-Regular.ttf! SDL_ttf Error: " << TTF_GetError() << std::endl;
        running = false;
        return;
    }
}

Game::~Game() {
    // TODO: Code cleanup method.
    if(font) TTF_CloseFont(font);
    if(fontL) TTF_CloseFont(fontL);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    TTF_Quit();
}

void Game::handleInput() {
    input.update();
}

void Game::render() {
    SDL_SetRenderDrawColor(ren, COL_BG.r, COL_BG.g, COL_BG.b, 255);
    SDL_RenderClear(ren);

    if (state == GameState::MENU) {
        SDL_SetRenderDrawColor(ren, 15, 20, 25, 255);
        for (int i = 0; i < SCREEN_WIDTH; i += 40) SDL_RenderDrawLine(ren, i, 0, i, SCREEN_HEIGHT);
        for (int i = 0; i < SCREEN_HEIGHT; i += 40) SDL_RenderDrawLine(ren, 0, i, SCREEN_WIDTH, i);
        // Intersections
        SDL_SetRenderDrawColor(ren, 30, 40, 50, 255);
        for (int x = 0; x < SCREEN_WIDTH; x += 40) {
            for (int y = 0; y < SCREEN_HEIGHT; y += 40) {
                SDL_Rect dot = { x - 1, y - 1, 3, 3 };
                SDL_RenderFillRect(ren, &dot);
            }
        }
    }

    if (state == GameState::MENU) {
        hud.renderMenu(ren, font, fontL);
    }

    SDL_RenderPresent(ren);
}

void Game::loop() { 
    while (running) { 
        Uint32 st = SDL_GetTicks(); 
        handleInput();
        render();
        Uint32 t = SDL_GetTicks() - st;
        if (t < FRAME_DELAY) SDL_Delay((Uint32)FRAME_DELAY - t);
    }
}