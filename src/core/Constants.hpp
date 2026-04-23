#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int TILE_SIZE = 40;
const int MAP_WIDTH = 50;
const int MAP_HEIGHT = 50;
const int TARGET_FPS = 60;
const int FRAME_DELAY = 1000.0f / TARGET_FPS;

const float PLAYER_SPEED = 220.0f;

const SDL_Color COL_BG = {5, 5, 10, 255};
const SDL_Color COL_WALL = {35, 40, 55, 255};
const SDL_Color COL_FLOOR = {15, 15, 20, 255};

#endif