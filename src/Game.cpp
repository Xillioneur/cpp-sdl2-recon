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