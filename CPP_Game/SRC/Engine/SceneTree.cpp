#include "SceneTree.h"

SceneTree* SceneTree::s_instance = nullptr;

SceneTree::SceneTree()
{}

SceneTree::~SceneTree()
{}

void SceneTree::UpdateNodes(SDL_Renderer* renderer, float deltaTime)
{
    for (auto const& [node, components] : nodes)
    {
        node->Update(deltaTime);
        for (Component* component : components)
        {
            component->Update(deltaTime);
            component->Render(renderer);
        }
    }
}



