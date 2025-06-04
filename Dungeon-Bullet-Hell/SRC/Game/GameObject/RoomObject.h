#pragma once
#include "Empty.h"
#include "../../Engine/GameObject.h"
#include "../../Engine/Components/Collider2D.h"
#include "../../Engine/Components/ColliderTileMap2D.h"
#include "../../Engine/Components/TileMap2D.h"

class RoomObject : public GameObject
{
public:
    void Ready() override;
    void Update(float deltaTime) override;
    void Activate();
    void Deactivate();

    Collider2D* triggerArea;

private:
    bool isRoomActive = false;
    Empty* door;
};
