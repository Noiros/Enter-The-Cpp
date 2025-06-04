#include "ObjectTileMap2D.h"
#include <fstream>
#include <sstream>
#include <glm.hpp>
#include <__msvc_ranges_to.hpp>

void ObjectTileMap2D::Ready()
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
                    glm::vec2 tilePos = {(static_cast<float>(x) * finalTileWidth + gameObject->transform->position.x), (static_cast<float>(y) * finalTileHeight + gameObject->transform->position.y)};
                    GameObject* newObj = SceneTree::Get().AddGameObjectByID(tileSetIndex);
                    if (newObj) {
                        Logger::Log("Add GameObject -> ID " + std::to_string(tileSetIndex) + " at (" + std::to_string(tilePos.x) + ", " + std::to_string(tilePos.y) + ")");
                        newObj->GetComponent<Transform2D>().position = glm::vec2(tilePos.x, tilePos.y);
                    }
                }
            }
        }
    }
}

void ObjectTileMap2D::ReadTileMapData(const std::string& filename)
{   
    std::ifstream file(filename);
    if (!file.is_open()) Logger::Err("Could not open map file!");

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