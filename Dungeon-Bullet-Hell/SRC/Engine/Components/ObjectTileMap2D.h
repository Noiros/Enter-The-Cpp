#pragma once
#include <string>

#include "TileMap2D.h"

class ObjectTileMap2D : public Component2D
{
public:
    ObjectTileMap2D(const std::string& mapData, size_t w, size_t h, float ftw, float fth) : width(w), height(h), finalTileWidth(ftw), finalTileHeight(fth)
    {
        ReadTileMapData(mapData);
    }
    ~ObjectTileMap2D() {};
    
    void Ready() override;
    void ReadTileMapData(const std::string& filename);

private:
    //Size of source tile
    static constexpr size_t tileHeight = 16;
    static constexpr size_t tileWidth = 16;
    //Size of the tilemap
    size_t tilemapHeight = 8;
    size_t tilemapWidth = 8;
    //Size of the map
    size_t width;
    size_t height;
    //Size of destination tiles
    float finalTileWidth = 16;
    float finalTileHeight = 16; 
    
    std::vector<uint32_t> tileMap;
};
