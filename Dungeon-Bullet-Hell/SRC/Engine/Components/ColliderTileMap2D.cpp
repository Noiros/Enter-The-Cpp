#include "ColliderTileMap2D.h"
#include <fstream>
#include <sstream>
#include "../Logger.h"

void ColliderTileMap2D::Ready()
{
    Component2D::Ready();

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (tileMap.size() > x + y * width)
            {
                uint32_t tileSetIndex = tileMap[x + y * width];
                if (tileSetIndex != -1)
                {
                    SDL_Rect dst = {(x * static_cast<int>(finalTileWidth)), (y * static_cast<int>(finalTileHeight)), static_cast<int>(finalTileWidth), static_cast<int>(finalTileHeight)};

                    CollisionShape collShape = dst;
                    gameObject->AddComponent<Collider2D>(collShape);
                }
            }
        }
    }
}

void ColliderTileMap2D::ReadTileMapData(const std::string& filename)
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
            uint32_t value = static_cast<uint32_t>(std::stoi(cell));
            tileMap.emplace_back(value);
        }
    }
    file.close();
}