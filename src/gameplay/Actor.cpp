#include "Actor.hpp"

namespace Graphics {
    void drawWeapon(SDL_Renderer* ren, Vec2 center, float lookAngle, int length, int width, SDL_Color col, float handOffset) {
        float handAngle = lookAngle + 1.5708f;
        Vec2 handPos = center + Vec2(std::cos(handAngle) * handOffset, std::sin(handAngle) * handOffset);
        float c = std::cos(lookAngle);
        float s = std::sin(lookAngle);
        int ex = (int)(handPos.x + c * length);
        int ey = (int)(handPos.y + s * length);
        SDL_SetRenderDrawColor(ren, col.r, col.g, col.b, 255);
        for (int i = -width/2; i <= width/2; ++i) {
            float ox = -s * i, oy = c * i;
            SDL_RenderDrawLine(ren, (int)(handPos.x + ox), (int)(handPos.y + oy), (int)(ex + ox), (int)(ey + oy));
        }
        SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(ren, 255, 50, 50, 50);
        SDL_RenderDrawLine(ren, (int)handPos.x, (int)handPos.y, (int)(handPos.x + c * 150.0f), (int)(handPos.y + s * 150.0f));
        SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_NONE);
    }
}

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
    Graphics::drawWeapon(ren, { (float)r.x + 12, (float)r.y + 12 }, lookAngle, 22, 6, {100, 110, 120, 255}, 0.0f);
    // TODO: Dash Timer
}