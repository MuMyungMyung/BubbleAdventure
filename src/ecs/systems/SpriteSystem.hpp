#pragma once

#include "ecs/ComponentManager.hpp"
#include "ecs/components/SpriteComponent.hpp"
#include "ecs/components/TransformComponent.hpp"
#include <SDL3/SDL_render.h>

class SpriteSystem {
  public:
    void render(SDL_Renderer *renderer, ComponentManager<SpriteComponent> &spriteManager,
        ComponentManager<TransformComponent> &transformManager);
};
