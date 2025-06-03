#include "CharacterMovement2D.h"

#include <SDL_timer.h>

#include "../GameObject.h"
#include "../Modules/SceneTree.h"
#include "../GameObject.h"

float timer = 0.0f;
float delay = 5000.0f;

void CharacterMovement2D::Update(float deltaTime)
{    
    transform->position += velocity * deltaTime;
}

void CharacterMovement2D::Ready()
{
    transform = &gameObject->GetComponent<Transform2D>();
}
