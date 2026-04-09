
#include "Entity.hpp"
#include "../core/Constants.hpp"

Entity::Entity(Vec2 p, float w, float h, EntityType t) : pos(pos), type(t) {
    bounds = {p.x, p.y, w, h};
}

void Entity::render(SDL_Renderer* ren, const Vec2& cam) {
    if (!active) return;
    SDL_Rect r = {(int)(pos.x - cam.x), (int)(pos.y - cam.y), (int)bounds.w, (int)bounds.h};
    SDL_SetRenderDrawColor(ren, 200, 200, 200, 255);
    SDL_RenderFillRect(ren, &r);
}