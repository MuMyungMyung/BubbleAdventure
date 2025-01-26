#pragma once

#include <string>
#include <vector>
#include <SDL3/SDL_render.h>
#include <unordered_map>
class Map {
  public:
    Map();
    void loadMap(const std::string &filename);
    void render(SDL_Renderer *renderer);

  private:
    size_t m_width;
    size_t m_height;
    size_t m_tileSize;
    std::vector<std::vector<int>> m_map;
    std::unordered_map<int, std::string> m_textureIds;
};
