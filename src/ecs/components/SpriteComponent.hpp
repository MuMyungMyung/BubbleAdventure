#pragma once

#include <string>
#include <SDL3/SDL_rect.h>
struct SpriteComponent {
    std::string textureID;
    SDL_FRect sourceRect;
    SDL_FRect destinationRect;
    bool flipHorizontally = false;
    bool flipVertically = false;

    SpriteComponent(const std::string &texID, SDL_FRect srcRect, SDL_FRect destRect)
        : textureID(texID), sourceRect(srcRect), destinationRect(destRect)
    {
    }
};
