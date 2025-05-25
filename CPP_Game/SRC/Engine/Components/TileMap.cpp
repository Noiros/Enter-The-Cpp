#include "TileMap.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm.hpp>

TileMap::~TileMap()
{
    Logger::Log("Level destructor called");
}

void TileMap::ReadTileMapData(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) Logger::Err("Error: Could not open map file!");

    tileMap.reserve(width * height);
    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream lineStream(line);
        std::string cell;

        while (std::getline(lineStream, cell, ','))
        {
            uint8_t value = static_cast<uint8_t>(std::stoi(cell));
            tileMap.emplace_back(value);
        }
    }
    file.close();
}

void TileMap::Update(float deltaTime)
{    
    
}

void TileMap::Render(SDL_Renderer* renderer)
{    
    for (size_t y = 0; y < height; y++)
        for (size_t x = 0; x < width; x++)
        {
            //source rectangle for the blit
            uint8_t tileSetIndex = tileMap[x + y * width];
            glm::ivec2 srcPos = {(tileSetIndex % tilemapWidth) * tileWidth, (tileSetIndex / tilemapHeight) * tileHeight};
            SDL_Rect src = {srcPos.x, srcPos.y, tileWidth, tileHeight};

            SDL_FRect dst = {static_cast<float>(x) * tileWidth, static_cast<float>(y) * tileHeight, tileWidth, tileHeight};

            //blit
            SDL_RenderCopyF(renderer, tileSetTexture, &src, &dst);
        }
}
