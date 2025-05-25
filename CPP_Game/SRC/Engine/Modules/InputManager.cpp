#include "InputManager.h"
#include "../Logger.h"

InputManager* InputManager::s_instance = nullptr;

InputManager::InputManager()
{
    Logger::Log("Input constructor called.");

    if (SDL_NumJoysticks() > 0 && SDL_IsGameController(0))
    {
        gameController = SDL_GameControllerOpen(0);
        Logger::Log("Game controller found.");
    }
}

InputManager::~InputManager()
{
    if (gameController) SDL_GameControllerClose(gameController);
    Logger::Log("Input destructor called.");
}

void InputManager::BindKey(Action action, SDL_Scancode key)
{
    keyBindings[action] = key;
}

void InputManager::BindButton(Action action, SDL_GameControllerButton button)
{
    buttonBindings[action] = button;
}

void InputManager::ProcessInput()
{
    heldKeys.clear();
    pressedKeys.clear();
    heldButtons.clear();
    pressedButtons.clear();

    const uint8_t* state = SDL_GetKeyboardState(nullptr);

    for (const auto& [action, key] : keyBindings)
    {
        if (state[key]) heldKeys.insert(key);
        if (state[key] && !heldKeys.contains(key)) pressedKeys.insert(key);
    }

    if (gameController)
    {
        for (const auto& [action, button] : buttonBindings)
        {
            if (SDL_GameControllerGetButton(gameController, button))
            {
                heldButtons.insert(button);
                if (!heldButtons.contains(button)) pressedButtons.insert(button);
            }
        }

        //read left stick axis
        leftStickX = SDL_GameControllerGetAxis(gameController, SDL_CONTROLLER_AXIS_LEFTX) / 32767.0f; //normalize
        leftStickY = SDL_GameControllerGetAxis(gameController, SDL_CONTROLLER_AXIS_LEFTY) / 32767.0f;

        //apply dead zone
        if (fabs(leftStickX) < DEAD_ZONE) leftStickX = 0.0f;
        if (fabs(leftStickY) < DEAD_ZONE) leftStickY = 0.0f;
    }
}

bool InputManager::IsActionHeld(Action action)
{
    return heldKeys.contains(keyBindings[action]) || heldButtons.contains(buttonBindings[action]);
}

bool InputManager::IsActionPressed(Action action)
{
    return pressedKeys.contains(keyBindings[action]) || pressedButtons.contains(buttonBindings[action]);
}

float InputManager::GetLeftStickX()
{
    return leftStickX;
}

float InputManager::GetLeftStickY()
{
    return leftStickY;
}
