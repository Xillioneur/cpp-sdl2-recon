
#include "Entity.hpp"
#include "../core/Constants.hpp"

Entity::Entity(Vec2 p, float w, float h, EntityType t) : pos(pos), type(t) {
    bounds = {p.x, p.y, w, h};
}