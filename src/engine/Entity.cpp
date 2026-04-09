
#include "Entity.hpp"
#include "../core/Constants.hpp"

Entity::Entity(Vec2 p, float w, float h, EntityType t) : pos(p), type(t) {
    bounds = {p.x, p.y, w, h};
}

void Entity::update(float dt, const std::vector<std::vector<Tile>>& map) {
    move(vel * dt, map);
}

void Entity::move(Vec2 delta, const std::vector<std::vector<Tile>>& map) {
    float dist = delta.length();
    if (dist <= 0) {
        bounds.x = pos.x;
        bounds.y = pos.y;
        return;
    }

    int steps = (int)(dist / 4.0f) + 1;
    Vec2 step = delta / (float)steps;

    for (int i = 0; i < steps; ++i) {
        if (std::abs(step.x) > 0.0001f) {
            pos.x += step.x;
            // TODO: collideMap.
        }
        if (std::abs(step.y) > 0.0001f) {
            pos.y += step.y;
            // TODO: collideMap.
        }
    }

    pos.x = std::clamp(pos.x, 40.0f, (MAP_WIDTH - 2) * 40.0f - bounds.w);
    pos.y = std::clamp(pos.y, 40.0f, (MAP_HEIGHT - 2) * 40.0f - bounds.h);
    bounds.x = pos.x;
    bounds.y = pos.y;
}

void Entity::render(SDL_Renderer* ren, const Vec2& cam) {
    if (!active) return;
    SDL_Rect r = {(int)(pos.x - cam.x), (int)(pos.y - cam.y), (int)bounds.w, (int)bounds.h};
    SDL_SetRenderDrawColor(ren, 200, 200, 200, 255);
    SDL_RenderFillRect(ren, &r);
}
