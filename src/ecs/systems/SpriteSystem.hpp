#pragma once

#include "ecs/ComponentManager.hpp"
#include "ecs/components/SpriteComponent.hpp"
#include "ecs/components/TransformComponent.hpp"
#include <SDL3/SDL_render.h>
#include <unordered_map>

class SpriteSystem {
  public:
    void render(SDL_Renderer *renderer, ComponentManager<SpriteComponent> &spriteManager,
        ComponentManager<TransformComponent> &positionManager)
    {
        for (auto &[entity, sprite] : spriteManager.getAllComponents()) {
            // Get the entity's position
            auto *position = positionManager.getComponent(entity);
            if (!position)
                continue;

            // Update destination rect based on the entity's position
            sprite.destinationRect.x = static_cast<int>(position->x);
            sprite.destinationRect.y = static_cast<int>(position->y);
            sprite.destinationRect.w = static_cast<int>(sprite.sourceRect.w * sprite.scale);
            sprite.destinationRect.h = static_cast<int>(sprite.sourceRect.h * sprite.scale);

            // Determine flip flags
            SDL_FlipMode flip = SDL_FLIP_NONE;
            if (sprite.flipHorizontally)
                flip = (SDL_FlipMode) (flip | SDL_FLIP_HORIZONTAL);
            if (sprite.flipVertically)
                flip = (SDL_FlipMode) (flip | SDL_FLIP_VERTICAL);

            // Render the sprite
            SDL_RenderTextureRotated(renderer, textureManager[sprite.textureID], &sprite.sourceRect,
                &sprite.destinationRect, (double) sprite.rotation, nullptr, flip);
        }
    }

    void addTexture(const std::string &id, SDL_Texture *texture)
    {
        textureManager[id] = texture;
    }

  private:
    // TODO
    std::unordered_map<std::string, SDL_Texture *> textureManager; // Maps texture IDs to SDL textures
};
