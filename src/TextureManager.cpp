#include "TextureManager.hpp"
#include <iostream>
#include <memory>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> TextureManager::textureCache;

SDL_Texture *TextureManager::loadTexture(const std::string &filepath, SDL_Renderer *renderer)
{
    if (textureCache.find(filepath) != textureCache.end()) {
        return textureCache[filepath].get();
    }

    SDL_Surface *surface = SDL_LoadBMP(filepath.c_str());

    if (!surface) {
        std::cerr << SDL_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    if (!texture) {
        std::cerr << SDL_GetError() << std::endl;
        return nullptr;
    }

    textureCache[filepath] = std::shared_ptr<SDL_Texture>(texture, SDL_DestroyTexture);
    return texture;
}

SDL_Texture *TextureManager::getTexture(const std::string &filepath)
{
    if (textureCache.find(filepath) != textureCache.end()) {
        return textureCache[filepath].get();
    }
    return nullptr;
}
