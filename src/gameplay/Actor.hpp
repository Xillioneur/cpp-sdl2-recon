#ifndef ACTOR_HPP
#define ACTOR_HPP

#include "../engine/Entity.hpp"

class Player : public Entity {
public:
    Player(Vec2 p);
    void update(float dt, const std::vector<std::vector<Tile>>& map) override;
    void render(SDL_Renderer* ren, const Vec2& cam) override;
};
#endif