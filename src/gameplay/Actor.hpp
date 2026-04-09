#ifndef ACTOR_HPP
#define ACTOR_HPP

#include "../engine/Entity.hpp"

class Player : public Entity {
public:
    Player(Vec2 p);
    void render(SDL_Renderer* ren, const Vec2& cam) override;
};
#endif