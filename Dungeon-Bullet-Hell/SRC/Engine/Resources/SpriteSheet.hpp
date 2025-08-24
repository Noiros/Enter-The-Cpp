#include <vec2.hpp>
#include "Sprite.h"
#include "../Utils.hpp"

class SpriteSheet : public Sprite
{
    public:
        SpriteSheet(std::string_view path, glm::vec2 size) : Sprite(path), tileSize(size) {}
    
        glm::vec2 tileSize = {16, 16};
        
        glm::vec2 GetFramePosition(int frame)
        {
            SDL_Point texSize = Utils::GetTextureSize(texture);
            
            int tilesPerRow = static_cast<int>(texSize.x / tileSize.x);

            int tileX = frame % tilesPerRow;
            int tileY = frame / tilesPerRow;

            return glm::vec2(static_cast<float>(tileX) * tileSize.x, static_cast<float>(tileY) * tileSize.y);
        }
};


