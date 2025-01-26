#pragma once

#include <memory>
#include <string>
#include <SDL3/SDL_render.h>
#include <unordered_map>

class TextureManager {
  public:
    static SDL_Texture *loadTexture(const std::string &filepath, SDL_Renderer *renderer);

    static SDL_Texture *getTexture(const std::string &filepath);

    static void cleanup();

  private:
    TextureManager() = default;

    static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> textureCache;
};
