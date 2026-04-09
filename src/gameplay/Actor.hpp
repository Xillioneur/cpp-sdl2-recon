#ifndef ACTOR_HPP
#define ACTOR_HPP

#include "../engine/Entity.hpp"

class Player : public Entity {
public:
    Player(Vec2 p);
};
#endif