#include "Map.hpp"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include "TextureManager.hpp"

using json = nlohmann::json;

Map::Map()
{
    m_textureIds[0] = "assets/sprites/dirt.bmp";
    m_textureIds[1] = "assets/sprites/rock.bmp";
    m_textureIds[2] = "assets/sprites/grass.bmp";
}

void Map::loadMap(const std::string &filename)
{
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open json file " + filename);
    }
    json mapJson;

    try {
        file >> mapJson;
        file.close();
    } catch (const std::exception &e) {
        std::cerr << "Error while trying to parse entities json: " << e.what() << std::endl;
        file.close();
        return;
    }

    m_width = mapJson["width"];
    m_height = mapJson["height"];
    m_tileSize = mapJson["tileSize"];
    m_map = mapJson["tiles"].get<std::vector<std::vector<int>>>();
}

void Map::render(SDL_Renderer *renderer)
{
    SDL_FRect src;
    SDL_FRect dst;

    src.x = 0;
    src.y = 0;
    src.w = m_tileSize;
    src.h = m_tileSize;
    dst.w = m_tileSize;
    dst.h = m_tileSize;

    for (size_t y = 0; y < m_map.size(); y++) {
        for (size_t x = 0; x < m_map[y].size(); x++) {
            int tileID = m_map[y][x];

            dst.x = x * m_tileSize;
            dst.y = y * m_tileSize;

            SDL_RenderTexture(renderer, TextureManager::getTexture(m_textureIds[tileID]), &src, &dst);
        }
    }
}
