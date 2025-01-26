#pragma once

#include "TextureManager.hpp"
#include "ecs/ComponentManager.hpp"
#include "ecs/components/SpriteComponent.hpp"
#include "ecs/components/TransformComponent.hpp"
#include <SDL3/SDL_render.h>

class SpriteSystem {
  public:
    void render(SDL_Renderer *renderer, ComponentManager<SpriteComponent> &spriteManager,
        ComponentManager<TransformComponent> &transformManager)
    {
        for (auto &[entity, sprite] : spriteManager.getAllComponents()) {
            // Get the entity's position
            auto *transform = transformManager.getComponent(entity);
            if (!transform)
                continue;

            // Update destination rect based on the entity's position
            sprite.destinationRect.x = static_cast<int>(transform->x);
            sprite.destinationRect.y = static_cast<int>(transform->y);
            sprite.destinationRect.w = static_cast<int>(sprite.sourceRect.w * transform->scale);
            sprite.destinationRect.h = static_cast<int>(sprite.sourceRect.h * transform->scale);

            // Determine flip flags
            SDL_FlipMode flip = SDL_FLIP_NONE;
            if (sprite.flipHorizontally)
                flip = (SDL_FlipMode) (flip | SDL_FLIP_HORIZONTAL);
            if (sprite.flipVertically)
                flip = (SDL_FlipMode) (flip | SDL_FLIP_VERTICAL);

            // Render the sprite
            SDL_RenderTextureRotated(renderer, TextureManager::getTexture(sprite.textureID), &sprite.sourceRect,
                &sprite.destinationRect, (double) transform->rotation, nullptr, flip);
        }
    }
};
