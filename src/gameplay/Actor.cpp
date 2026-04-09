#include "Actor.hpp"

Player::Player(Vec2 p) : Entity(p, 24, 24, EntityType::PLAYER) {}
void Player::update(float dt, const std::vector<std::vector<Tile>>& map) {
    Entity::update(dt, map);
}
void Player::render(SDL_Renderer* ren, const Vec2& cam) {
    SDL_Rect r = {(int)(pos.x - cam.x), (int)(pos.y - cam.y), (int)bounds.w, (int)bounds.h};
    SDL_SetRenderDrawColor(ren, 40, 45, 55, 255);
    SDL_RenderFillRect(ren, &r);
    SDL_SetRenderDrawColor(ren, 20, 20, 25, 255);
    SDL_RenderDrawRect(ren, &r);
    SDL_Rect chest = {r.x + 4, r.y + 4, 16, 16};
    SDL_SetRenderDrawColor(ren, 60, 70, 80, 255); 
    SDL_RenderFillRect(ren, &chest);
    SDL_Rect visor = {r.x + 6, r.y + 2, 12, 4};
    SDL_SetRenderDrawColor(ren, 100, 255, 255, 255); 
    SDL_RenderFillRect(ren, &visor);
    // TODO: Draw Weapon
    // TODO: Dash Timer
}