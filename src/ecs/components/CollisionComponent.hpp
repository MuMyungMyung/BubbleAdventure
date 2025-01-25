#pragma once

#include <SDL3/SDL_rect.h>
struct CollisionComponent {
    float x;
    float y;
    float width;
    float height;

    // Collision settings
    bool isTrigger = false; // Whether this entity triggers events instead of blocking
    bool isStatic = false;  // Whether the entity is immovable (walls)

    int collisionLayer = 0; // Layer index (player, enemy, environment, items)

    SDL_FRect GetBoundingBox() const
    {
        return SDL_FRect{x, y, width, height};
    }
};
