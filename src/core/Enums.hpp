#ifndef ENUMS_HPP
#define ENUMS_HPP

#include "Rect.hpp"
#include <SDL2/SDL.h>

enum class GameState { MENU, PLAYING };
enum TileType { WALL, FLOOR, HAZARD_TILE };

struct Tile {
    TileType type;
    Rect rect;
};

#endif