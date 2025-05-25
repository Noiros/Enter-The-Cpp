#pragma once
#include <vector>
#include <string>
#include <SDL.h>
#include "../Logger.h"
#include "../../Game/Game.h"

class TileMap : public Component
{
    public:
        TileMap(SDL_Texture* t, const std::string& mapData, size_t w, size_t h) : tileSetTexture(t), width(w), height(h)
        {
            Logger::Log("Level constructor called");
            ReadTileMapData(mapData);
        }

        ~TileMap();
    
        void Update(float deltaTime) override;
        void Ready() override {}
        void Render(SDL_Renderer* renderer) override;

    private:
        void ReadTileMapData(const std::string& filename);

        SDL_Texture* tileSetTexture;

        //Taille d'une tile
        static constexpr size_t tileHeight = 32;
        static constexpr size_t tileWidth = 32;
        //Nombre de tiles sur le tilemap
        static constexpr size_t tilemapHeight = 8;
        static constexpr size_t tilemapWidth = 8;
        //Taille de la map en tiles
        size_t width;
        size_t height;
    
        std::vector<uint8_t> tileMap; //assuming we do not have a tileset larger than 256 indices

        //camera stuff (could be in its own class)
        const float initCamPosY = height * tileHeight - DISPLAY_HEIGHT;
        float camPosY = initCamPosY;
        float camSpeed = 50.0f;

        //other data such as enemies or pickups initial pos/time or attack patterns could be stored here
};
