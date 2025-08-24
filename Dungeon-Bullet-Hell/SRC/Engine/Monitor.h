#pragma once
#include "Engine.h"
#include "GameObject.h"
#include "Components/LabelUI.h"

class Monitor : public GameObject
{
public:
    LabelUI* fpsLabel;
    LabelUI* UpdateMSLabel;
    LabelUI* renderMSLabel;
    LabelUI* msLabel;

    float updateRate = 1.0f;
    float currentTime = 0.0f;

    Engine* engine;

    void Ready() override;
    void Update(float deltaTime) override;
};
