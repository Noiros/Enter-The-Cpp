#include "Movement.h"

#include "../Modules/SceneTree.h"

void Movement::Update(float deltaTime)
{
    SceneTree* sceneTree = &SceneTree::GetInstance();
    Node* ParentNode = sceneTree->GetRootNode(this);
    Transform* transform = sceneTree->GetComponent<Transform>(ParentNode);
    
    transform->position += velocity * deltaTime;
}