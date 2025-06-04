#pragma once
#include <SDL_render.h>
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
    //Taille d'une tile
    static constexpr size_t tileHeight = 16;
    static constexpr size_t tileWidth = 16;
    //Nombre de tiles sur le tilemap
    size_t tilemapHeight = 8;
    size_t tilemapWidth = 8;
    //Taille de la map en tiles
    size_t width;
    size_t height;
    //Taille des tiles rendues en pixels
    float finalTileWidth = 16;
    float finalTileHeight = 16; 
    
    std::vector<uint32_t> tileMap;
};
