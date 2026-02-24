#include "Game.hpp"
#include <iostream>

Game::Game() {
    win = SDL_CreateWindow("Recon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

Game::~Game() {
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
}

void Game::render() {
    SDL_SetRenderDrawColor(ren, COL_BG.r, COL_BG.g, COL_BG.b, 255);
    SDL_RenderClear(ren);
    SDL_RenderPresent(ren);
}

void Game::loop() { 
    while (running) { 
        Uint32 st = SDL_GetTicks(); 
        render();
        Uint32 t = SDL_GetTicks() - st;
        if (t < FRAME_DELAY) SDL_Delay((Uint32)FRAME_DELAY - t);
    }
}