#pragma once

#include <string>
#include <SDL3/SDL_rect.h>
struct SpriteComponent {
    std::string textureID;
    SDL_FRect sourceRect;
    SDL_FRect destinationRect;
    float scale = 1.0f;
    bool flipHorizontally = false;
    bool flipVertically = false;

    float rotation = 0.0f;

    SpriteComponent(const std::string &texID, SDL_FRect srcRect, SDL_FRect destRect, float spriteScale = 1.0f)
        : textureID(texID), sourceRect(srcRect), destinationRect(destRect), scale(spriteScale)
    {
    }
};
