#pragma once
#include <vector>
#include <string>
#include <SDL.h>
#include "../Logger.h"
#include "../../Game/Game.h"

class TileMap2D : public Component2D
{
    public:
        TileMap2D(SDL_Texture* t, const std::string& mapData, size_t w, size_t h, float ftw, float fth) : tileSetTexture(t), width(w), height(h), finalTileWidth(ftw), finalTileHeight(fth)
        {
            Logger::Log("Level constructor called");
            SDL_Point tileSetTextureSize = GetTextureSize(tileSetTexture);
            tilemapWidth = tileSetTextureSize.x / tileWidth;
            tilemapHeight = tileSetTextureSize.y / tileHeight;
            ReadTileMapData(mapData);
        }
        ~TileMap2D();
    
        void Update(float deltaTime) override;
        void Render(SDL_Renderer* renderer, glm::vec2 cameraPos, float cameraScale) override;

    private:
        void ReadTileMapData(const std::string& filename);

        SDL_Texture* tileSetTexture;

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

        SDL_Point GetTextureSize(SDL_Texture *texture) {
            SDL_Point size;
            SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
            return size;
        }
};
