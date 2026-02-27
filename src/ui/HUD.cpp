#include "HUD.hpp"
#include "../Game.hpp"
#include <algorithm>
#include <iostream>

void HUD::renderMenu(SDL_Renderer* ren, TTF_Font* font, TTF_Font* fontL) {
    renderText(ren, "RECOIL PROTOCOL", SCREEN_WIDTH / 2 - 180, 150, fontL, {100, 200, 255, 255});
    renderText(ren, "NEURAL INTERFACE INITIALIZED", SCREEN_WIDTH / 2 - 120, 220, font, {200, 200, 255, 255});
    
    int ty = 280;
    renderText(ren, "OPERATIONAL MANUAL:", SCREEN_WIDTH / 2 - 80, ty, font, {150, 150, 150, 255});
    renderText(ren, "[WASD] - MOBILE LINK", SCREEN_WIDTH / 2 - 100, ty + 25, font, {200, 200, 200, 255});
    renderText(ren, "[MOUSE1] - KINETIC DISCHARGE", SCREEN_WIDTH / 2 - 100, ty + 45, font, {200, 200, 200, 255});
    renderText(ren, "[SHIFT] - TACHYON DASH", SCREEN_WIDTH / 2 - 100, ty + 65, font, {200, 200, 200, 255});
    renderText(ren, "[SPACE] - REFLEX OVERRIDE", SCREEN_WIDTH / 2 - 100, ty + 85, font, {200, 200, 200, 255});
    renderText(ren, "[1-3] - AMMO SELECTION", SCREEN_WIDTH / 2 - 100, ty + 105, font, {200, 200, 200, 255});
    
    renderText(ren, "PRESS ENTER TO COMMENCE MISSION", SCREEN_WIDTH / 2 - 160, 480, font, {100, 255, 100, 255});
    renderText(ren, "CREATED BY GEMINI-CLI // SYSTEM VERSION 1.0.3", SCREEN_WIDTH / 2 - 180, SCREEN_HEIGHT - 30, font, {80, 80, 100, 255});
}

void HUD::renderText(SDL_Renderer* ren, const std::string& t, int x, int y, TTF_Font* f, SDL_Color c) {
    if (!f || t.empty()) return;
    // Bloom shadow
    SDL_Color bloom = c; bloom.a = 60;
    SDL_Surface* bs = TTF_RenderText_Blended(f, t.c_str(), bloom);
    if (bs) {
        SDL_Texture* bt = SDL_CreateTextureFromSurface(ren, bs);
        SDL_Rect bd = {x - 1, y - 1, bs->w + 2, bs->h + 2};
        SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
        SDL_RenderCopy(ren, bt, NULL, &bd);
        SDL_DestroyTexture(bt); SDL_FreeSurface(bs);
    }

    SDL_Surface* s = TTF_RenderText_Blended(f, t.c_str(), c);
    if (s) {
        SDL_Texture* tx = SDL_CreateTextureFromSurface(ren, s);
        SDL_Rect dst = {x, y, s->w, s->h};
        SDL_RenderCopy(ren, tx, NULL, &dst);
        SDL_DestroyTexture(tx);
        SDL_FreeSurface(s);
    }
}