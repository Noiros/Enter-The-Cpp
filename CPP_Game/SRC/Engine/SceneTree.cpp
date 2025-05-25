#include "SceneTree.h"
#include "../Game/Player.h"
#include "Component.h"

void SceneTree::UpdateNodes(SDL_Renderer* renderer, float deltaTime)
{
    for (Node* node : nodes)
    {
        node->Update(deltaTime);
    }
    for (Component* component : components)
    {
        component->Update(deltaTime);
        component->Render(renderer);
    }
}



