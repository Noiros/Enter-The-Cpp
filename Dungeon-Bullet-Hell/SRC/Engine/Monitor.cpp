#include "Monitor.h"

void Monitor::Ready()
{
    GameObject::Ready();

    engine = &Engine::Get();

    fpsLabel = &AddComponent<LabelUI>("", 20, 0, 80);
    UpdateMSLabel = &AddComponent<LabelUI>("", 20, 0, 110);
    renderMSLabel = &AddComponent<LabelUI>("", 20, 0, 140);
    msLabel = &AddComponent<LabelUI>("", 20, 0, 170);
}

void Monitor::Update(float deltaTime)
{
    GameObject::Update(deltaTime);

    currentTime += deltaTime;
    if (currentTime >= updateRate)
    {
        currentTime = 0;
        fpsLabel->text =      "FPS : " + std::to_string(1000.0f / engine->millisFrame);
        UpdateMSLabel->text = "Update Time : " + std::to_string(engine->millisUpdateFrame) + "ms";
        renderMSLabel->text = "Render Time : " + std::to_string(engine->millisRenderFrame) + "ms";
        msLabel->text =       "Frame Time : " + std::to_string(engine->millisFrame) + "ms";
    }
}
