#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>
#include <SDL2/SDL.h>
#include "../core/Vec2.hpp"
#include "../core/Rect.hpp"
#include "../core/Enums.hpp"

class Entity {
public:
    Vec2 pos;
    Vec2 vel;
    Rect bounds;
    EntityType type;
    bool active = true;
    float lookAngle = 0.0f;

    Entity(Vec2 p, float w, float h, EntityType t);
    virtual ~Entity() {}
};

#endif