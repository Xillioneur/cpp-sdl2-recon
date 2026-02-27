#ifndef HUD_HPP
#define HUD_HPP

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Game;

class HUD {
public:
    void renderMenu(SDL_Renderer* ren, TTF_Font* font, TTF_Font* fontL);
    void renderText(SDL_Renderer* ren, const std::string& t, int x, int y, TTF_Font* f, SDL_Color c);
};

#endif