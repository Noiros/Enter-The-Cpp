#include "CharacterMovement2D.h"

#include "../Modules/SceneTree.h"

void CharacterMovement2D::Update(float deltaTime)
{
    SceneTree* sceneTree = &SceneTree::GetInstance();
    Node* ParentNode = sceneTree->GetRootNode(this);
    Transform2D* transform = sceneTree->GetComponent<Transform2D>(ParentNode);
    
    transform->position += velocity * deltaTime;
}